#ifndef __FONT_H__
#define __FONT_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <sys/mman.h>
#include <string>
#include <vector>
// #include "student_head.h"
#include "sysres.h"


#define color u32
#define getColor(a, b, c, d) (a | (b << 8) | (c << 16) | (d << 24))

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

typedef struct stbtt_fontinfo {
    void* userdata;
    unsigned char* data;              // pointer to .ttf file
    int fontstart;                    // offset of start of font
    int numGlyphs;                    // number of glyphs, needed for range checking
    int loca, head, glyf, hhea, hmtx, kern; // table locations as offset from start of .ttf
    int index_map;                    // a cmap mapping for our chosen character encoding
    int indexToLocFormat;             // format needed to map from glyph index to glyph
} stbtt_fontinfo;

typedef struct {
    u32 height;
    u32 width;
    u32 byteperpixel;
    u8* map;
} bitmap;

class Font {
public:
    Font(const std::string& fontPath);
    ~Font();

    void setSize(s32 pixels);
    bitmap* createBitmap(u32 width, u32 height, u32 byteperpixel);
    bitmap* createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c);
    void print(bitmap* screen, s32 x, s32 y, const std::string& text, color c, s32 maxWidth);
    void showToLcd(unsigned int* p, int px, int py, bitmap* bm);
    void unload();

private:
    stbtt_fontinfo* info;
    u8* buffer;
    float scale;
};

class ListView {
public:
    ListView(int x, int y, int dis_width, int dis_height, int layout_width, int layout_height, const std::string& list_info, const std::string& image);
    ~ListView();

    void display(sys_res_t *sysres);
    void slide(int ts_x, int ts_y, int prev_x, int prev_y, sys_res_t *sysres);
    void click(int ts_x, int ts_y, sys_res_t *sysres);
    void load();

private:
    int x, y;
    Font* ft; // 字库的资源
    bitmap bm; // 显示所需的位图
    int offset_x, offset_y;
    int display_width, display_height;
    int layout_width, layout_height;
    unsigned int *layout_mem; // 用来记录缓冲的内存地址
    std::string list_info; // 用来记录列表上的信息
    std::string image; // 用来记录列表控件背景的图片
    student_node_t *list_head; // 记录学生信息的头节点
    int layout_x = 0, layout_y = 0; // 记录布局的偏移

    void display_layout_to_framebuffer(int fb_x, int fb_y, int width, int height, unsigned int *fb_addr);
    void traverse_student_list();
};

// LCD设备结构体
struct LcdDevice {
    int fd;
    unsigned int* mp; // 保存映射首地址
};

// C接口函数声明
#ifdef __cplusplus
extern "C" {
#endif

// 1. 初始化字库
Font* fontLoad(const char* fontPath);

// 2. 设置字体的大小
void fontSetSize(Font* f, s32 pixels);

// 3. 设置字体输出框的大小
bitmap* createBitmap(u32 width, u32 height, u32 byteperpixel);

// 可以指定输出框的颜色
bitmap* createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c);

// 4. 把字体输出到输出框中
void fontPrint(Font* f, bitmap* screen, s32 x, s32 y, const char* text, color c, s32 maxWidth);

// 5. 把输出框的所有信息显示到LCD屏幕中
void show_font_to_lcd(unsigned int* p, int px, int py, bitmap* bm);

// 关闭字体库
void fontUnload(Font* f);

// 关闭 bitmap
void destroyBitmap(bitmap* bm);

ListView* request_list_view(int x, int y, int dis_width, int dis_height, int layout_width, int layout_height, const char *list_info, const char *image);
void destroy_list_view(ListView* view);

#ifdef __cplusplus
}
#endif

#endif // __FONT_H__
