#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "gumbo.h"

#define _XOPEN_SOURCE 600

#include <SDL2/SDL.h>
#include <time.h>

#include "render.h"
#include "surface.h"

#define W 1920
#define H 1080

static std::string handle_unknown_tag(GumboStringPiece *text)
{
    std::string tagname = "";
    if (text->data == NULL)
    {
        return tagname;
    }
    // work with copy GumboStringPiece to prevent asserts
    // if try to read same unknown tag name more than once
    GumboStringPiece gsp = *text;
    gumbo_tag_from_original_text(&gsp);
    tagname = std::string(gsp.data, gsp.length);
    return tagname;
}

static std::string get_tag_name(GumboNode *node)
{
    std::string tagname;
    // work around lack of proper name for document node
    if (node->type == GUMBO_NODE_DOCUMENT)
    {
        tagname = "document";
    }
    else
    {
        tagname = gumbo_normalized_tagname(node->v.element.tag);
    }
    if (tagname.empty())
    {
        tagname = handle_unknown_tag(&node->v.element.original_tag);
    }
    return tagname;
}

static void draw_rectangle_tag(surface_t *base, const GumboVector *attributes)
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int radius = 0;
    color_t fill_color = {0, 0, 0, 255};
    for (unsigned int i = 0; i < attributes->length; ++i)
    {
        GumboAttribute *attr = (GumboAttribute *)attributes->data[i];
        std::string name = attr->name;

        if (name == "x")
        {
            x = std::atoi(attr->value);
        }
        else if (name == "y")
        {
            y = std::atoi(attr->value);
        }
        else if (name == "width")
        {
            width = std::atoi(attr->value);
        }
        else if (name == "height")
        {
            height = std::atoi(attr->value);
        }
        else if (name == "radius")
        {
            radius = std::atoi(attr->value);
        }
        else if (name == "fill-color")
        {
            unsigned int c = 0;
            if(attr->value[0] == '#')
            {
                c = std::stoul(attr->value + 1, nullptr, 16);
            }
            fill_color = ARGB(c);
        }
    }
    draw_rectangle(base, x, y, width, height, radius, (style_t){
        fill_color : fill_color,
        border_radius : {1, 1, 1, 1},
    });
}

static void scan_html(surface_t *base, const GumboNode *root)
{
    assert(root->type == GUMBO_NODE_ELEMENT);
    GumboVector *head_children = (GumboVector *)&root->v.element.children;
    for (int i = 0; i < head_children->length; ++i)
    {
        GumboNode *child = (GumboNode *)head_children->data[i];

        if (child->type == GUMBO_NODE_ELEMENT)
        {

            std::string name = get_tag_name(child);

            if (name == "Rectangle")
            {
                draw_rectangle_tag(base, &child->v.element.attributes);
            }
            scan_html(base, child);
        }
        else if (child->type == GUMBO_NODE_TEXT || child->type == GUMBO_NODE_WHITESPACE)
        {
        }
    }
}

int parse_html_file(surface_t *base, const char *filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in)
    {
        std::cout << "File " << filename << " not found!\n";
        exit(EXIT_FAILURE);
    }

    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    GumboOptions options = kGumboDefaultOptions;

    GumboOutput *output = gumbo_parse_with_options(&options, contents.data(), contents.length());
    scan_html(base, output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

static SDL_Window *gWindow = NULL;
static SDL_Surface *gSurface = NULL;

static void frambuffer_init()
{
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Gate", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
    gSurface = SDL_GetWindowSurface(gWindow);
}

static void frambuffer_close()
{
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, const char **argv)
{
    frambuffer_init();
    surface_t surface;
    surface_wrap(&surface, (color_t *)gSurface->pixels, W, H);
    surface_clear(&surface, RGB(0xFFFFFF), 0, 0, surface.width, surface.height);
    parse_html_file(&surface, "examples/html/test.html");
    SDL_UpdateWindowSurface(gWindow);

    while (1)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
                break;
            }
        }
    }
}