#include <cstring>
#include "bmp.hpp"
#include "font.hpp"

using namespace std;

// Constructor
ListView::ListView(int x, int y, int dis_width, int dis_height, int layout_width, int layout_height, const string& list_info, const string& image)
    : x(x), y(y), display_width(dis_width), display_height(dis_height), layout_width(layout_width),
      layout_height(layout_height), list_info(list_info), image(image) {
    
    layout_mem = (unsigned int*)malloc(layout_width * layout_height * sizeof(unsigned int)); // 申请内存
    list_head = request_student_node(NULL); // 初始化链表头节点
    ft = fontLoad("/usr/share/fonts/DroidSansFallback.ttf"); // 加载字体
    fontSetSize(ft, 30);
    
    bm.height = layout_height;
    bm.width = layout_width;
    bm.byteperpixel = 4;
    bm.map = (void *)layout_mem; // 映射内存
}

// Destructor
ListView::~ListView() {
    destroy_student_list(list_head);
    destroy_student_node(list_head);
    free(layout_mem); // 释放内存
}

void ListView::display_layout_to_framebuffer(int fb_x, int fb_y, int width, int height, unsigned int *fb_addr) {
    for (int row = 0; row < height; row++) {
        memcpy(fb_addr + 800 * (fb_y + row) + fb_x, layout_mem + layout_width * row, width * sizeof(unsigned int));
    }
}

void ListView::display(sys_res_t *sysres) {
    display_layout_to_framebuffer(x, y, display_width, display_height, sysres->fb_addr);
}

void ListView::slide(int ts_x, int ts_y, int prev_x, int prev_y, sys_res_t *sysres) {
    int offset_x = ts_x - prev_x;
    int offset_y = ts_y - prev_y;

    layout_x -= offset_x;
    layout_y -= offset_y;

    if (layout_x < 0) layout_x = 0;
    if (layout_x + display_width > 800) layout_x = 800 - display_width;

    if (layout_y < 0) layout_y = 0;
    if (layout_y + display_height > 480) layout_y = 480 - display_height;

    display(sysres);
}

// 遍历学生信息并渲染到列表中
void ListView::traverse_student_list() {
    int x_coord = 10;
    int y_coord = 10;

    struct list_head *pos;
    student_node_t *bpos;

    list_for_each(pos, &list_head->list) {
        bpos = list_entry(pos, student_node_t, list);
        fontPrint(ft, &bm, x_coord, y_coord, bpos->data.name, getColor(0, 0, 0, 0), 0);
        y_coord += 40;
    }
}

void ListView::load() {
    decompress_jpeg_to_memory(image.c_str(), 0, 0, layout_width, layout_height, layout_mem, 1.0);
    load_student_info(list_head);
    traverse_student_list();
}

// C 接口的实现
extern "C" {
    ListView* request_list_view(int x, int y, int dis_width, int dis_height, int layout_width, int layout_height, const char *list_info, const char *image) {
        return new ListView(x, y, dis_width, dis_height, layout_width, layout_height, list_info, image);
    }

    void destroy_list_view(ListView* view) {
        delete view; // 使用 delete 释放 C++ 对象
    }
}
