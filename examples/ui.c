#include "surface.h"
#include "render.h"
#include "image.h"

#define W 1485
#define H 1050

static const char *resource[] = {
    "M18.618182 671.465484v1.059571h18.012712l34.05765-66.298891 3.935551 39.506874L3.027347 735.645233v220.542202l12.714856 13.320326 6.811529 21.494161-8.325203 17.255875v15.136734H105.957132v-15.136734l-45.410199-57.216851v-131.992313l34.057649-52.978566 15.136734-15.136734v40.566445l36.176792 164.990392v0.756837l17.255876 10.444346 12.866223 24.067405-8.022469 17.104509v15.136733h90.820399v-15.136733l-53.584035-60.546933-33.300813-128.813599 19.82912-66.450259 109.287214-136.230599c58.881892 27.700222 129.873171 31.78714 188.452328 31.78714a671.919586 671.919586 0 0 0 81.435625-9.384775h58.42779l6.962897 186.030451-9.687509 130.47864v1.059572l18.16408 13.320325 6.81153 21.342794-8.022469 17.255875v15.136734h91.577236v-15.136734l-46.167036-60.546932v-90.820399l31.333037-126.54309 23.916039 93.847746 9.536142 128.964967v0.908204l20.585957 13.320325 10.444346 21.494161-4.843755 17.104509v15.136733h90.820399v-15.136733l-47.377975-51.464893-25.732446-108.37901 24.521508-274.58034a18.012712 18.012712 0 0 0 1.362306-2.27051 389.619512 389.619512 0 0 0 30.273466-89.60946l14.077162-53.432669 74.775462-136.230598 120.185661 19.223651 18.466815 11.655285H1135.254989l26.489283-41.928751v-43.896527l-94.75595-72.05085-25.429712-45.410199-12.260753-9.536142 9.838876-21.645529L1060.630894 60.546933v-0.908204L1041.861345 15.136733V14.228529L987.823208 1.665041 956.641537 0l-111.709091 0.908204 1.210939 27.397487-82.041094 19.223651 3.632816 33.906283-72.353584 26.64065-3.178714 56.308647-63.120178 44.047894 10.141611 44.501996-59.487361 37.084996 8.930673 16.044937h-146.523578l-182.549002-22.402365h-37.539098c-105.957132 0-199.653511 86.884848-199.653511 185.424981l-21.191426 88.54989L8.627938 590.332594 0 630.29357z",
    "M736 800H352a32 32 0 0 1 0-64h352V320a32 32 0 0 1 64 0v448a32 32 0 0 1-32 32z m-128-128H288a32 32 0 0 1-32-32V256a32 32 0 0 1 32-32h320a32 32 0 0 1 32 32v384a32 32 0 0 1-32 32z m-288-64h256V288h-256v320z",
    "M516.4 233.6c152.7 0 277 124.3 277 277 0 33.3-5.2 68.6-14.9 102-9.5 32.4-22.7 61-38.1 82.6l-15.9 22.3 10.2 25.4 17.9 44.8H516.4c-152.7 0-277-124.3-277-277s124.3-277.1 277-277.1m0-50c-180.3 0-327 146.7-327 327s146.7 327 327 327h310l-45.3-113.4c38-53.1 62.3-136.1 62.3-213.6 0-180.4-146.7-327-327-327z",
    "M667.1 550.4c69.2-48.9 114-128.3 114-217.8C781.1 184 661 63.9 512.4 63.9S243.7 184 243.7 332.6c0 89.6 44.8 171 114 217.8C215.1 611.5 113.4 754 113.4 918.9c0 22.4 18.3 40.7 40.7 40.7s40.7-18.3 40.7-40.7c0-175.1 142.5-317.6 317.6-317.6S830 743.8 830 918.9c0 22.4 18.3 40.7 40.7 40.7s40.7-18.3 40.7-40.7c0-164.9-99.7-307.4-244.3-368.5z m-342-217.8c0-103.8 83.5-187.3 187.3-187.3s187.3 83.5 187.3 187.3-83.5 187.3-187.3 187.3-187.3-83.5-187.3-187.3z",
    "M400.774803 401.775596l-111.407346 0 0 334.237387 111.407346 0L400.774803 401.775596zM623.599727 67.538209 512.187265 67.538209l0 668.474774 111.412462 0L623.599727 67.538209zM846.424652 234.657414 735.01219 234.657414l0 501.355569 111.412462 0L846.424652 234.657414zM177.949878 847.425446 177.949878 67.538209 66.537416 67.538209l0 891.299699 891.299699 0L957.837114 847.425446 177.949878 847.425446z",
    "M881 512c0-52.4 32.9-96.8 79-114.5-11-43.2-28-83.9-50.2-121.3C864.6 296.3 810 288.1 773 251c-37-37-45.2-91.7-25.1-136.8C710.4 92 669.7 75 626.5 64c-17.8 46.1-62.2 79-114.5 79-52.4 0-96.8-32.9-114.5-79-43.2 11-83.9 28-121.3 50.2 20.1 45.2 11.9 99.8-25.1 136.8-37 37-91.7 45.2-136.8 25.2C92 313.6 75 354.3 64 397.5c46.1 17.8 79 62.2 79 114.5 0 52.4-32.9 96.8-79 114.5 11 43.2 28 83.9 50.2 121.3C159.4 727.7 214 735.9 251 773c37 37 45.2 91.7 25.1 136.8C313.6 932 354.3 949 397.5 960c17.8-46.1 62.2-79 114.5-79 52.4 0 96.8 32.9 114.5 79 43.2-11 83.9-28 121.3-50.2-20.1-45.2-11.9-99.8 25.1-136.8 37-37 91.7-45.2 136.8-25.2C932 710.4 949 669.7 960 626.5c-46.1-17.7-79-62.1-79-114.5zM512 635c-67.9 0-123-55.1-123-123s55.1-123 123-123 123 55.1 123 123-55.1 123-123 123z",
    "M846.304267 413.609677L312.02119 22.283078A116.140167 116.140167 0 0 0 128.457154 120.290311v783.100137a116.395561 116.395561 0 0 0 183.947126 98.198778l533.899987-391.007358a123.03579 123.03579 0 0 0 0-196.972191z",
    "M876.479155 247.554142 540.475542 247.554142l-28.018124-40.447201c-28.67611-53.323463-36.21583-80.893378-80.893378-80.893378l-283.128359 0c-44.677549 0-80.893378 36.21583-80.893378 80.893378l0 121.340579 0 40.447201 0 444.915116c0 44.677549 36.21583 80.893378 80.893378 80.893378l728.043475 0c44.677549 0 80.893378-36.21583 80.893378-80.893378L957.372533 328.447521C957.373557 283.769972 921.156704 247.554142 876.479155 247.554142z",
    "M1010.602099 946.388128l-233.305883-233.013336A437.503384 437.503384 0 0 0 437.722794 0 437.503384 437.503384 0 0 0 0 437.35711a437.503384 437.503384 0 0 0 437.722794 437.357111 435.601831 435.601831 0 0 0 275.140041-97.198596l233.305884 233.086474a45.344717 45.344717 0 0 0 64.360243 0 45.417854 45.417854 0 0 0 0-64.287107z m-434.431645-181.378868a353.249974 353.249974 0 0 1-138.44766 27.86506 355.2978 355.2978 0 0 1-355.73662-355.444073 354.493297 354.493297 0 0 1 104.146576-251.44377 354.42016 354.42016 0 0 1 251.590044-104.07344 355.2978 355.2978 0 0 1 355.736619 355.444073 354.493297 354.493297 0 0 1-104.146576 251.44377 357.638172 357.638172 0 0 1-113.142383 76.20838z",
    "M786.199893 237.267627 674.85696 141.284693 1087.597227 141.284693C1108.964693 141.284693 1126.372693 158.692693 1126.372693 180.06016L1126.372693 237.267627 786.199893 237.267627ZM1126.372693 888.122027C1126.372693 909.55776 1108.964693 927.034027 1087.597227 927.034027L141.216427 927.034027C119.84896 927.034027 102.372693 909.55776 102.372693 888.122027L102.372693 107.15136C102.372693 85.715627 119.84896 68.23936 141.216427 68.23936L485.62176 68.23936 760.804693 305.534293 1126.372693 305.534293 1126.372693 888.122027ZM1087.597227 73.018027 595.667627 73.018027 511.01696-0.027307 141.216427-0.027307C82.16576-0.027307 34.106027 48.100693 34.106027 107.15136L34.106027 888.122027C34.106027 947.172693 82.16576 995.300693 141.216427 995.300693L1087.597227 995.300693C1146.647893 995.300693 1194.63936 947.172693 1194.63936 888.122027L1194.63936 252.96896 1194.63936 237.267627 1194.63936 180.06016C1194.63936 121.009493 1146.647893 73.018027 1087.597227 73.018027L1087.597227 73.018027Z", //FIXME
    "M728.981333 42.666667a42.666667 42.666667 0 0 1 30.186667 12.501333l124.352 124.394667A42.666667 42.666667 0 0 1 896 209.728V938.666667a42.666667 42.666667 0 0 1-42.666667 42.666666H170.666667a42.666667 42.666667 0 0 1-42.666667-42.666666V85.333333a42.666667 42.666667 0 0 1 42.666667-42.666666h558.314666zM682.666667 128H213.333333v768h597.333334V256.810667l-106.666667 0.021333a21.333333 21.333333 0 0 1-21.333333-21.333333L682.645333 128zM490.666667 704a21.333333 21.333333 0 0 1 21.333333 21.333333v42.666667a21.333333 21.333333 0 0 1-21.333333 21.333333h-170.666667a21.333333 21.333333 0 0 1-21.333333-21.333333v-42.666667a21.333333 21.333333 0 0 1 21.333333-21.333333h170.666667z m213.333333-170.666667a21.333333 21.333333 0 0 1 21.333333 21.333334v42.666666a21.333333 21.333333 0 0 1-21.333333 21.333334H320a21.333333 21.333333 0 0 1-21.333333-21.333334v-42.666666a21.333333 21.333333 0 0 1 21.333333-21.333334h384z m0-170.666666a21.333333 21.333333 0 0 1 21.333333 21.333333v42.666667a21.333333 21.333333 0 0 1-21.333333 21.333333H320a21.333333 21.333333 0 0 1-21.333333-21.333333v-42.666667a21.333333 21.333333 0 0 1 21.333333-21.333333h384z",
    "M914.9 611.7h-18.5V191.8h18.5c25.3 0 46.1-20.8 46.1-46.1 0-25.4-20.7-46.1-46.1-46.1H110.8c-25.4 0-46.1 20.7-46.1 46.1 0 25.4 20.7 46.1 46.1 46.1h17.9v419.9h-17.9c-25.4 0-46.1 20.7-46.1 46.1 0 25.4 20.7 46.1 46.1 46.1h19.6c0.4 0.2 0.8 0.3 1.3 0.3h88c0.4 0 0.9-0.1 1.2-0.3h245.6v158.7h-65.6c-26.6 0-48.3 21.7-48.3 48.3s21.7 48.3 48.3 48.3h224.2c26.5 0 48.2-21.7 48.2-48.3s-21.7-48.3-48.3-48.3h-65.5V703.9h244.6c0.4 0.2 0.8 0.3 1.3 0.3h88c0.5 0 0.9-0.1 1.3-0.3h20.2c25.3 0 46.1-20.8 46.1-46.1 0-25.4-20.7-46.1-46.1-46.1zM222.7 191.8h579.7v419.9H222.7V191.8zM754.4 292.8c-18.9-18.9-49.9-18.9-68.8 0L607 376.4 574.6 344c-9.5-9.5-22-14.2-34.4-14.2-12.5 0-25 4.7-34.5 14.2l-51.8 52.4-49-43.4c-0.7-0.8-1.4-1.5-2.1-2.2-18.9-18.9-49.9-18.9-68.8 0l-63.1 64.1c-18.9 18.9-18.9 49.9 0 68.8s49.9 18.9 68.8 0l30.9-31.3 49 43.4c0.6 0.7 1.3 1.4 2 2.1 18.9 18.9 49.9 18.9 68.8 0l50-50.5 32.5 32.5c0.1 0.1 0.2 0.2 0.4 0.3 0.1 0.1 0.2 0.2 0.3 0.4 18.9 18.9 49.9 18.9 68.8 0l112-119c18.9-18.9 18.9-49.9 0-68.8z",
    "M896 64a64 64 0 0 1 64 64v768a64 64 0 0 1-64 64H128a64 64 0 0 1-64-64V128a64 64 0 0 1 64-64h768m0-64H128a128 128 0 0 0-128 128v768a128 128 0 0 0 128 128h768a128 128 0 0 0 128-128V128a128 128 0 0 0-128-128zM1024 320H0v64h1024V320zM1024 640H0v64h1024v-64zM384 320H320v704h64V320zM704 320h-64v704h64V320z",
    "M265.1 509.8c-0.1 45.5-36.8 82.2-82.4 82.1-45.4-0.1-82.3-37-82.2-82.5 0-45.3 37.1-82.2 82.6-82.1 45.4 0.1 82 36.9 82 82.5z m577-82.4c45.5 0 82.5 36.8 82.5 82.2 0.1 45.4-36.8 82.4-82.3 82.4-45.6 0-82.4-36.6-82.4-82.2s36.6-82.4 82.2-82.4zM512.4 592c-45.4 0-82.6-37.3-82.4-82.4 0.3-45.5 37.1-82.2 82.6-82.2 45.4 0 82.5 37.1 82.3 82.4-0.1 45.4-37 82.2-82.5 82.2z",
    "M469.8 397c-1.2 54.8-46.7 98.3-101.5 97-54.8-1.2-98.3-46.7-97-101.5 1.2-54.1 45.5-97.3 99.6-97.1 55.3 0.9 99.5 46.3 98.9 101.6z m420 314L714.3 471s-10.1-19.4-46.3-19.4c-36.2 0-53 19-53 19L461.2 714c-6 10.2-16.9 16.5-28.7 16.4-12.9 0.5-25.2-5.7-32.5-16.4l-80.3-94.8c-11.3-15.6-28.6-25.9-47.8-28.4-26.9 0-49.3 31.4-49.3 31.4L134.2 736V240.2c-0.2-15.7 12.3-28.5 28-28.7h699.6c15.7 0.2 28.2 13.1 28 28.7V711zM876 138.7H148c-47 0.6-84.6 39.2-84 86.2v574.2c-0.6 47 37 85.6 84 86.2h728c47-0.6 84.6-39.2 84-86.2V224.9c0.6-47-37-85.6-84-86.2z",
    "M682.325618 390.030222a126.008889 126.008889 0 0 1-91.818667-39.822222 138.467556 138.467556 0 0 1-37.774222-96.711111l0.910222-210.488889a37.717333 37.717333 0 0 1 21.788445-34.133333 34.417778 34.417778 0 0 1 38.513777 7.395555l308.736 309.191111a38.684444 38.684444 0 0 1 8.476445 40.96 35.612444 35.612444 0 0 1-33.109334 23.552h-215.722666z m250.311111 69.973334H651.378062a163.726222 163.726222 0 0 1-119.466666-52.224 180.451556 180.451556 0 0 1-49.152-125.838223l1.137777-274.204444A43.008 43.008 0 0 1 484.57984 0H257.877618A176.924444 176.924444 0 0 0 85.333618 180.849778v662.300444A176.867556 176.867556 0 0 0 257.650062 1024h508.700445A176.867556 176.867556 0 0 0 938.666951 843.150222V459.491556a58.311111 58.311111 0 0 1-6.144 0.512z m-219.591111 405.617777H310.898062a40.903111 40.903111 0 0 1 0-81.692444h402.147556a40.903111 40.903111 0 0 1-0.113778 81.692444z m0-167.310222H310.898062a40.846222 40.846222 0 0 1 0-81.635555h402.147556a40.846222 40.846222 0 0 1-0.113778 81.635555z",
    "M1096.757895 0H88.926316C16.168421 0 0 13.473684 0 94.315789v838.063158C0 1007.831579 16.168421 1024 88.926316 1024h1007.831579c72.757895 0 88.926316-13.473684 88.926316-94.315789v-835.368422C1185.684211 16.168421 1172.210526 0 1096.757895 0zM374.568421 762.610526V261.389474L811.115789 512l-436.547368 250.610526z",
    "M136.615057 0A50.123969 50.123969 0 0 0 100.656558 15.255121 54.482575 54.482575 0 0 0 85.401437 51.213621v921.572758A50.123969 50.123969 0 0 0 100.656558 1007.92764a51.486034 51.486034 0 0 0 35.958499 15.255121h750.769886a49.579143 49.579143 0 0 0 35.958499-15.255121 50.396382 50.396382 0 0 0 15.255121-35.958499V290.119713L648.478851 0zM938.598563 290.119713h-238.906092a52.575685 52.575685 0 0 1-51.21362-51.213621V0zM548.503325 454.384677a34.596435 34.596435 0 0 0-38.955041-36.775738 68.920458 68.920458 0 0 0-53.120511 27.241287l-34.868848-32.417132a123.947858 123.947858 0 0 1 95.072094-45.220537c53.120511 0 91.803139 27.241288 91.803139 81.723862 0 64.561852-77.910082 72.189412-71.372173 132.665071h-54.482576c-10.896515-68.920458 65.923916-84.720404 65.923916-127.216813z m-38.955041 156.36499a41.406757 41.406757 0 0 1 43.58606 43.041235 41.67917 41.67917 0 0 1-44.403299 42.223996A41.67917 41.67917 0 0 1 464.60016 653.790902a41.406757 41.406757 0 0 1 44.130885-43.041235z",
    "M170.666667 469.333333m42.666666 0l597.333334 0q42.666667 0 42.666666 42.666667l0 0q0 42.666667-42.666666 42.666667l-597.333334 0q-42.666667 0-42.666666-42.666667l0 0q0-42.666667 42.666666-42.666667ZM170.666667 213.333333m42.666666 0l256 0q42.666667 0 42.666667 42.666667l0 0q0 42.666667-42.666667 42.666667l-256 0q-42.666667 0-42.666666-42.666667l0 0q0-42.666667 42.666666-42.666667ZM170.666667 725.333333m42.666666 0l597.333334 0q42.666667 0 42.666666 42.666667l0 0q0 42.666667-42.666666 42.666667l-597.333334 0q-42.666667 0-42.666666-42.666667l0 0q0-42.666667 42.666666-42.666667Z",
    "M1020.399619 580.499104H585.024043v435.372581h-145.123528V580.499104H4.524939v-145.123528h435.37258V0.002995h145.123528v435.372581h435.372581v145.123528z",

};
surface_t *image[3] = {0};

int sample(surface_t *base, float fps)
{
    surface_clear(base, RGB(0xBCC4D0), 0, 0, base->width, base->height);
	printf("fps:%f\n", fps);

    int x = 5, y = 5;

    //menu
    draw_rectage(base, x, y, 81, 1041, 18, (style_t){
        fill_color : RGB(0x5864FF),
        border_radius : {
            [0] = 1,
            [3] = 1,
        }
    });
    {
        int x = 5, y = 5;
        draw_circle(base, 42, 45, 24, (style_t){
            fill_color : RGB(0xFFFFFF),
        });

        draw_svg(base, resource[0], 1024, 1024, 25, 25, 42 - 12, 45 - 12, RGB(0x5864FF));
        draw_svg(base, resource[1], 1024, 1024, 45, 45, 20, 127, RGB(0xFFFFFF));
        draw_svg(base, resource[2], 1024, 1024, 35, 35, 25, 214, RGB(0xFFFFFF));
        draw_svg(base, resource[3], 1024, 1024, 25, 25, 30, 294, RGB(0xFFFFFF));
        draw_svg(base, resource[4], 1024, 1024, 25, 25, 30, 384, RGB(0xFFFFFF)); // FIXME
        draw_svg(base, resource[5], 1024, 1024, 25, 25, 30, 474, RGB(0xFFFFFF));
        draw_rectage(base, x, y + 114, 2, 67, 0, (style_t){
            fill_color : RGB(0xFFFFFF),
        });
        draw_rectage(base, x + 2, y + 114, 81 - 2, 67, 0, (style_t){
            fill_color : ARGB(0x1FFFFFFF),
        });
    }

    //content
    draw_rectage(base, x + 81, y, 1391, 1041, 18, (style_t){
        fill_color : RGB(0xF6F8FB),
        border_radius : {
            [1] = 1,
            [2] = 1,
        }
    });
    {
        int x = 5 + 81, y = 5;

        //left
        draw_rectage(base, x, y, 261, 1041, 18, (style_t){
            fill_color : RGB(0xFFFFFF),
        });
        {
            int x = 5 + 81, y = 5;

            draw_text(base, x + 26, y + 24, "Marketing Team", 1.2, RGB(0));
            draw_text(base, x + 26, y + 54, "17 members", 1, RGB(0x9FA4C6));
            draw_text(base, x + 26, y + 117, "Storage", 1.5, RGB(0));
            draw_text(base, x + 26, y + 164, "My Files", 1.2, RGB(0x6570F7));

            {
                int x = 5 + 81 + 26, y = 5 + 206;
                draw_svg(base, resource[6], 1024, 1024, 8, 8, x + 11, y + 5, RGB(0x7780AF));
                draw_svg(base, resource[7], 1024, 1024, 18, 18, x + 30, y, RGB(0xAAAFCD));
                draw_text(base, x + 55, y + 2, "Analytics", 0.9, RGB(0x283480));
            }

            {
                int x = 5 + 81 + 26, y = 5 + 206 + 37;
                draw_svg(base, resource[6], 1024, 1024, 8, 8, x + 11, y + 5, RGB(0x7780AF));
                draw_svg(base, resource[7], 1024, 1024, 18, 18, x + 30, y, RGB(0xAAAFCD));
                draw_text(base, x + 55, y + 2, "Assets", 0.9, RGB(0x283480));
            }
            {
                int x = 5 + 81 + 26, y = 5 + 206 + 37 + 37;
                draw_svg(base, resource[6], 1024, 1024, 8, 8, x + 11, y + 5, RGB(0x7780AF));
                draw_svg(base, resource[7], 1024, 1024, 18, 18, x + 30, y, RGB(0xAAAFCD));
                draw_text(base, x + 55, y + 2, "Marketing", 0.9, RGB(0x283480));
            }
            {
                int x = 5 + 81 + 26, y = 5 + 206 + 37 + 37 + 37;
                draw_svg(base, resource[6], 1024, 1024, 8, 8, x + 11, y + 5, RGB(0x7780AF));
                draw_svg(base, resource[7], 1024, 1024, 18, 18, x + 30, y, RGB(0xAAAFCD));
                draw_text(base, x + 55, y + 2, "Templates", 0.9, RGB(0x283480));
            }
            {
                int x = 5 + 81 + 26, y = 5 + 206 + 37 + 37 + 37 + 37;
                draw_svg(base, resource[6], 1024, 1024, 8, 8, x + 11, y + 5, RGB(0x7780AF));
                draw_svg(base, resource[7], 1024, 1024, 18, 18, x + 30, y, RGB(0xAAAFCD));
                draw_text(base, x + 55, y + 2, "Projects", 0.9, RGB(0x283480));
            }
            {
                int x = 5 + 81 + 26, y = 5 + 206 + 37 + 37 + 37 + 37 + 37;
                draw_svg(base, resource[6], 1024, 1024, 8, 8, x + 11, y + 5, RGB(0x7780AF));
                draw_svg(base, resource[7], 1024, 1024, 18, 18, x + 30, y, RGB(0xAAAFCD));
                draw_text(base, x + 55, y + 2, "Projector", 0.9, RGB(0x283480));
            }

            draw_text(base, x + 26, y + 438, "Shared with me", 1, RGB(0x212E7C));
            draw_text(base, x + 26, y + 438 + 43, "Recent", 1, RGB(0x212E7C));
            draw_text(base, x + 26, y + 438 + 43 + 43, "Starred", 1, RGB(0x212E7C));
            draw_text(base, x + 26, y + 438 + 43 + 43 + 43, "Trash", 1, RGB(0x212E7C));

            draw_rectage(base, x + 25, y + 708, 214, 239, 8, (style_t){
                fill_color : RGB(0xF6F8FB),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 25, y = 5 + 708;

                draw_text(base, x + 61, y + 26, "Folder", 1.1, RGB(0x2A3681));
                draw_text(base, x + 61, y + 26 + 58, "Text Doc", 1.1, RGB(0x2A3681));
                draw_text(base, x + 61, y + 26 + 58 + 40, "Presentation", 1.1, RGB(0x2A3681));
                draw_text(base, x + 61, y + 26 + 58 + 40 + 40, "Sheets", 1.1, RGB(0x2A3681));
                draw_text(base, x + 61, y + 26 + 58 + 40 + 40 + 40, "More", 1.1, RGB(0x2A3681));

                draw_svg(base, resource[9], 1024, 1024, 15, 15, x + 20, y + 26, RGB(0x6B76F7));
                draw_svg(base, resource[10], 1024, 1024, 18, 18, x + 20, y + 26 + 58, RGB(0x6B76F7));
                draw_svg(base, resource[11], 1024, 1024, 18, 18, x + 20, y + 26 + 58 + 40, RGB(0x6B76F7));
                draw_svg(base, resource[12], 1024, 1024, 18, 18, x + 20, y + 26 + 58 + 40 + 40, RGB(0x6B76F7));
                draw_svg(base, resource[13], 1024, 1024, 18, 18, x + 20, y + 26 + 58 + 40 + 40 + 40, RGB(0x6B76F7));
            }

            draw_rectage(base, x + 25, y + 708 + 239 + 20, 214, 53, 8, (style_t){
                fill_color : RGB(0x5864FF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 25, y = 5 + 708 + 239 + 20;

                draw_text(base, x + 37, y + 18, "Create new", 1.2, RGB(0xFFFFFF));
                draw_rectage(base, x + 168, y + 8, 37, 37, 5, (style_t){
                    fill_color : RGB(0x7983FF),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    int x = 5 + 81 + 25 + 168, y = 5 + 708 + 239 + 20 + 8;

                    draw_svg(base, resource[19], 1024, 1024, 12, 12, x + 13, y + 13, RGB(0xFDFEFF));
                }
            }
        }

        //Center
        {
            int x = 5 + 81 + 261, y = 5;
            //search
            draw_rectage(base, x + 25, y + 27, 716, 52, 8, (style_t){
                fill_color : RGB(0xFFFFFF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 + 25, y = 5 + 27;
                draw_svg(base, resource[8], 1024, 1024, 18, 18, x + 20, y + 15, RGB(0x6B76F7));

                draw_text(base, x + 66, y + 19, "Search the files", 1.1, RGB(0xD6D6E3));
            }

            draw_rectage(base, x - 18, y + 115, 267, 209, 8, (style_t){
                fill_color : RGB(0x5864FF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 - 18, y = 5 + 115;

                if (!image[0])
                {
                    image[0] = surface_image_load("res/1.jpg", 66, 66);
                }

                draw_rectage(base, x + 19, y + 19, 65, 65, 10, (style_t){
                    fill_color : RGB(0x0),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    },
                    clip_image : image[0]
                });
                draw_text(base, x + 19, y + 105, "Google Drive", 1.2, RGB(0xF7F8FF));
                draw_text(base, x + 19, y + 151, "45.5 GB", 1.0, RGB(0xDADDFE));
                draw_text(base, x + 197, y + 151, "50 GB", 1.0, RGB(0xDADDFE));
            }
            draw_rectage(base, x + 273, y + 129, 225, 174, 8, (style_t){
                fill_color : RGB(0xFFFFFF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 + 273, y = 5 + 129;
                if (!image[1])
                {
                    image[1] = surface_image_load("res/2.png", 66, 66);
                }
                draw_rectage(base, x + 16, y + 16, 52, 52, 8, (style_t){
                    fill_color : RGB(0xF6F8FB),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    },
                    clip_image : image[1]

                });

                draw_text(base, x + 18, y + 88, "Dropbox", 1.2, RGB(0x172576));
                draw_text(base, x + 18, y + 125, "1,2 GB", 1.0, RGB(0x414C8F));
                draw_text(base, x + 173, y + 125, "3 GB", 1.0, RGB(0x414C8F));
            }
            draw_rectage(base, x + 520, y + 129, 225, 174, 8, (style_t){
                fill_color : RGB(0xFFFFFF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 + 520, y = 5 + 129;
                draw_rectage(base, x + 16, y + 16, 52, 52, 8, (style_t){
                    fill_color : RGB(0xF6F8FB),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });

                if (!image[2])
                {
                    image[2] = surface_image_load("res/3.png", 66, 66);
                }
                draw_rectage(base, x + 16, y + 16, 52, 52, 8, (style_t){
                    fill_color : RGB(0xF6F8FB),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    },
                    clip_image : image[2]
                });

                draw_text(base, x + 18, y + 88, "OneDrive", 1.2, RGB(0x172576));
                draw_text(base, x + 18, y + 125, "12,5 GB", 1.0, RGB(0x414C8F));
                draw_text(base, x + 173, y + 125, "3 GB", 1.0, RGB(0x414C8F));
            }
            draw_text(base, x + 25, y + 359, "Folders", 1.2, RGB(0));
            draw_text(base, x + 680, y + 363, "View all", 0.9, RGB(0x505EED));
            draw_rectage(base, x + 25, y + 408, 225, 117, 8, (style_t){
                fill_color : RGB(0xFFFFFF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 + 25, y = 5 + 408;
                draw_svg(base, resource[7], 1024, 1024, 32, 32, x + 17, y + 19, RGB(0x5864FF));
                draw_text(base, x + 17, y + 61, "Analytics", 1.1, RGB(0x293681));
                draw_text(base, x + 17, y + 86, "15 files", 0.9, RGB(0x9CA2C4));
            }
            draw_rectage(base, x + 274, y + 408, 225, 117, 8, (style_t){
                fill_color : RGB(0xFFFFFF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 + 274, y = 5 + 408;
                draw_svg(base, resource[7], 1024, 1024, 32, 32, x + 17, y + 19, RGB(0x5864FF));
                draw_text(base, x + 17, y + 61, "Assets", 1.1, RGB(0x293681));
                draw_text(base, x + 17, y + 86, "345 files", 0.9, RGB(0x9CA2C4));
            }
            draw_rectage(base, x + 521, y + 408, 225, 117, 8, (style_t){
                fill_color : RGB(0xFFFFFF),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 + 521, y = 5 + 408;
                draw_svg(base, resource[7], 1024, 1024, 32, 32, x + 17, y + 19, RGB(0x5864FF));
                draw_text(base, x + 17, y + 61, "Marketing", 1.1, RGB(0x293681));
                draw_text(base, x + 17, y + 86, "143 files", 0.9, RGB(0x9CA2C4));
            }
            draw_text(base, x + 25, y + 572, "Recent Files", 1.2, RGB(0));
            draw_text(base, x + 680, y + 576, "View all", 0.9, RGB(0x505EED));

            //Files
            {
                int x = 5 + 81 + 261 + 25, y = 5 + 624;

                draw_text(base, x + 0, y + 5, "Name", 0.9, RGB(0x6B75A9));
                draw_text(base, x + 367, y + 5, "Members", 0.9, RGB(0x6B75A9));
                draw_text(base, x + 532, y + 5, "Last modified", 0.9, RGB(0x6B75A9));
            }

            {
                int x = 5 + 81 + 261 + 25, y = 5 + 662;
                draw_rectage(base, x, y, 28, 28, 2, (style_t){
                    fill_color : RGB(0xFF6760),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    int x = 5 + 81 + 261 + 25, y = 5 + 662;
                    draw_text(base, x + 5, y + 8, "PDF", 0.7, RGB(0xFFFFFF));
                }
                draw_text(base, x + 47, y + 5, "Competitor Analysis Template", 1, RGB(0x303D85));
                draw_text(base, x + 367, y + 5, "Only you", 1, RGB(0x858DB8));
                draw_text(base, x + 532, y + 5, "Sep 3, 2019", 1, RGB(0x858DB8));
                draw_svg(base, resource[13], 1024, 1024, 18, 18, x + 532 + 149, y + 2, RGB(0x858DB8));
            }

            {
                int x = 5 + 81 + 261 + 25, y = 5 + 662 + 62;
                draw_rectage(base, x, y, 28, 28, 2, (style_t){
                    fill_color : RGB(0x6394FF),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    draw_svg(base, resource[18], 1024, 1024, 15, 15, x + 5, y + 6, RGB(0xFFFFFF));
                }
                draw_text(base, x + 47, y + 5, "How to Create a Case Study", 1, RGB(0x303D85));
                draw_text(base, x + 367, y + 5, "3 members", 1, RGB(0x858DB8));
                draw_text(base, x + 532, y + 5, "Jun 12, 2019", 1, RGB(0x858DB8));
                draw_svg(base, resource[13], 1024, 1024, 18, 18, x + 532 + 149, y + 2, RGB(0x858DB8));
            }

            {
                int x = 5 + 81 + 261 + 25, y = 5 + 662 + 62 + 62;
                draw_rectage(base, x, y, 28, 28, 2, (style_t){
                    fill_color : RGB(0x6394FF),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    draw_svg(base, resource[18], 1024, 1024, 15, 15, x + 5, y + 6, RGB(0xFFFFFF));
                }
                draw_text(base, x + 47, y + 5, "Landing Page Structure", 1, RGB(0x303D85));
                draw_text(base, x + 367, y + 5, "10 members", 1, RGB(0x858DB8));
                draw_text(base, x + 532, y + 5, "Jul 17, 2019", 1, RGB(0x858DB8));
                draw_svg(base, resource[13], 1024, 1024, 18, 18, x + 532 + 149, y + 2, RGB(0x858DB8));
            }
            {
                int x = 5 + 81 + 261 + 25, y = 5 + 662 + 62 + 62 + 62;
                draw_rectage(base, x, y, 28, 28, 2, (style_t){
                    fill_color : RGB(0xFF6760),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    draw_text(base, x + 5, y + 8, "PDF", 0.7, RGB(0xFFFFFF));
                }
                draw_text(base, x + 47, y + 5, "Meeting Report", 1, RGB(0x303D85));
                draw_text(base, x + 367, y + 5, "5 members", 1, RGB(0x858DB8));
                draw_text(base, x + 532, y + 5, "Aug 28, 2019", 1, RGB(0x858DB8));
                draw_svg(base, resource[13], 1024, 1024, 18, 18, x + 532 + 149, y + 2, RGB(0x858DB8));
            }
            {
                int x = 5 + 81 + 261 + 25, y = 5 + 662 + 62 + 62 + 62 + 62;
                draw_rectage(base, x, y, 28, 28, 2, (style_t){
                    fill_color : RGB(0xFBC02D),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    draw_text(base, x + 5, y + 8, "ZIP", 0.7, RGB(0xFFFFFF));
                }
                draw_text(base, x + 47, y + 5, "Project Documents", 1, RGB(0x303D85));
                draw_text(base, x + 367, y + 5, "Only you", 1, RGB(0x858DB8));
                draw_text(base, x + 532, y + 5, "Aug 17, 2019", 1, RGB(0x858DB8));
                draw_svg(base, resource[13], 1024, 1024, 18, 18, x + 532 + 149, y + 2, RGB(0x858DB8));
            }
            {
                int x = 5 + 81 + 261 + 25, y = 5 + 662 + 62 + 62 + 62 + 62 + 62;
                draw_rectage(base, x, y, 28, 28, 2, (style_t){
                    fill_color : RGB(0x6394FF),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    draw_svg(base, resource[18], 1024, 1024, 15, 15, x + 5, y + 6, RGB(0xFFFFFF));
                }
                draw_text(base, x + 47, y + 5, "Review Checklist Template", 1, RGB(0x303D85));
                draw_text(base, x + 367, y + 5, "7 members", 1, RGB(0x858DB8));
                draw_text(base, x + 532, y + 5, "Sep 8, 2019", 1, RGB(0x858DB8));
                draw_svg(base, resource[13], 1024, 1024, 18, 18, x + 532 + 149, y + 2, RGB(0x858DB8));
            }
        }

        //right
        draw_rectage(base, x + 261 + 765, y, 1391 - 261 - 765, 1041, 18, (style_t){
            fill_color : RGB(0xFFFFFF),
            border_radius : {
                [1] = 1,
                [2] = 1,
            }

        });

        {
            int x = 5 + 81 + 261 + 765, y = 5;
            draw_text(base, x + 23, y + 38, "45.5 GB", 2, RGB(0x4957EC));
            draw_text(base, x + 242, y + 38, "50 GB", 2, RGB(0xC5C8DD));
            draw_text(base, x + 23, y + 83, "Used", 1.2, RGB(0xA9AECD));
            draw_text(base, x + 242, y + 83, "Upgrade", 1.2, RGB(0x6D78F7));

            {
                int x = 5 + 81 + 261 + 765 + 23, y = 5 + 156;

                draw_rectage(base, x, y, 49, 49, 7, (style_t){
                    fill_color : RGB(0xEFF0FE),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }

                });
                {
                    draw_svg(base, resource[14], 1024, 1024, 18, 18, x + 15, y + 15, RGB(0x6B76F7));
                }
                draw_text(base, x + 63, y + 6, "Images", 1, RGB(0x333F87));
                draw_text(base, x + 63, y + 30, "1,756 files", 0.9, RGB(0x9197BE));
                draw_text(base, x + 242, y + 17, "15.3 GB", 1.1, RGB(0x4957EC));
            }

            {
                int x = 5 + 81 + 261 + 765 + 23, y = 5 + 156 + 73;

                draw_rectage(base, x, y, 49, 49, 7, (style_t){
                    fill_color : RGB(0xE6FAF3),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }

                });
                {
                    draw_svg(base, resource[15], 1024, 1024, 18, 18, x + 15, y + 15, RGB(0x16D090));
                }
                draw_text(base, x + 63, y + 6, "Documents", 1, RGB(0x333F87));
                draw_text(base, x + 63, y + 30, "123 files", 0.9, RGB(0x9197BE));
                draw_text(base, x + 242, y + 17, "256 MB", 1.1, RGB(0x4957EC));
            }

            {
                int x = 5 + 81 + 261 + 765 + 23, y = 5 + 156 + 73 + 73;

                draw_rectage(base, x, y, 49, 49, 7, (style_t){
                    fill_color : RGB(0xFFEFEE),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }

                });
                {
                    draw_svg(base, resource[16], 1024, 1024, 15, 15, x + 15, y + 15, RGB(0xFF6760));
                }
                draw_text(base, x + 63, y + 6, "Media Files", 1, RGB(0x333F87));
                draw_text(base, x + 63, y + 30, "24 files", 0.9, RGB(0x9197BE));
                draw_text(base, x + 242, y + 17, "3.4 GB", 1.1, RGB(0x4957EC));
            }

            {
                int x = 5 + 81 + 261 + 765 + 23, y = 5 + 156 + 73 + 73 + 73;

                draw_rectage(base, x, y, 49, 49, 7, (style_t){
                    fill_color : RGB(0xFEF8E7),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }

                });
                {
                    draw_svg(base, resource[15], 1024, 1024, 18, 18, x + 15, y + 15, RGB(0xFDBE00));
                }
                draw_text(base, x + 63, y + 6, "Other Files", 1, RGB(0x333F87));
                draw_text(base, x + 63, y + 30, "454 files", 0.9, RGB(0x9197BE));
                draw_text(base, x + 242, y + 17, "3 GB", 1.1, RGB(0x4957EC));
            }

            {
                int x = 5 + 81 + 261 + 765 + 23, y = 5 + 156 + 73 + 73 + 73 + 73;

                draw_rectage(base, x, y, 49, 49, 7, (style_t){
                    fill_color : RGB(0xEFF4FF),
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }

                });
                {
                    draw_svg(base, resource[17], 1024, 1024, 18, 18, x + 15, y + 15, RGB(0x6194FF));
                }
                draw_text(base, x + 63, y + 6, "Unknown Files", 1, RGB(0x333F87));
                draw_text(base, x + 63, y + 30, "57 files", 0.9, RGB(0x9197BE));
                draw_text(base, x + 242, y + 17, "175 MB", 1.1, RGB(0x4957EC));
            }
            draw_rectage(base, x + 23, y + 534, 309, 484, 16, (style_t){
                fill_color : RGB(0xF4F6FA),
                border_radius : {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1,
                    [3] = 1,
                }
            });
            {
                int x = 5 + 81 + 261 + 23, y = 300;

                //upgrade
                draw_rectage(base, x + 26, y + 23, 335, 509, 16, (style_t){
                    fill_color : ARGB(0x3FFFFFFF),
                    stroke_color : RGB(0xD1D4F4),
                    background_blur : 15,
                    stroke_width : 2,
                    border_radius : {
                        [0] = 1,
                        [1] = 1,
                        [2] = 1,
                        [3] = 1,
                    }
                });
                {
                    int x = 5 + 81 + 261 + 23 + 26, y = 300 + 23;
                    draw_text(base, x + 59, y + 304, "Upgrade account!", 1.5, RGB(0x1D289B));
                    draw_text(base, x + 33, y + 353, "5 integrations, 30 team members,", 1.0, RGB(0x6D74BF));
                    draw_text(base, x + 53, y + 379, "advanced features for teams", 1.0, RGB(0x6D74BF));

                    draw_rectage(base, x + 89, y + 419, 155, 50, 8, (style_t){
                        fill_color : RGB(0x5864FF),
                        border_radius : {
                            [0] = 1,
                            [1] = 1,
                            [2] = 1,
                            [3] = 1,
                        }
                    });
                    draw_text(base, x + 130, y + 436, "Upgrade", 1.2, RGB(0xFFFFFF));
                }
            }
        }
    }
}

#include "main.h"