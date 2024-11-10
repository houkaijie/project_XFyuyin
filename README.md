## 项目 智能语音识别小平板

文件结构：
C:.
├─clientWav
├─linux_aitalk
│  ├─bin
│  │  ├─msc
│  │  │  ├─c6d461b3d673a43cc7d5e54f61e0c0c2
│  │  │  └─res
│  │  │      └─asr
│  │  │          └─GrmBuilld
│  │  │              └─temp
│  │  └─wav
│  ├─doc
│  ├─include
│  ├─libs
│  │  ├─x64
│  │  └─x86
│  └─samples
│      ├─asr_offline_record_sample
│      └─asr_offline_sample
└─lvgl_arm
    ├─clientWav
    ├─lib
    ├─login
    ├─lvgl
    │  ├─demos
    │  │  ├─benchmark
    │  │  │  └─assets
    │  │  ├─keypad_encoder
    │  │  ├─music
    │  │  │  └─assets
    │  │  ├─stress
    │  │  └─widgets
    │  │      └─assets
    │  ├─docs
    │  │  ├─get-started
    │  │  │  ├─bindings
    │  │  │  ├─os
    │  │  │  └─platforms
    │  │  ├─intro
    │  │  ├─layouts
    │  │  ├─libs
    │  │  ├─misc
    │  │  ├─others
    │  │  ├─overview
    │  │  │  └─renderers
    │  │  ├─porting
    │  │  ├─widgets
    │  │  ├─_ext
    │  │  ├─_static
    │  │  │  ├─css
    │  │  │  ├─img
    │  │  │  └─js
    │  │  └─_templates
    │  ├─env_support
    │  │  ├─cmake
    │  │  ├─cmsis-pack
    │  │  ├─rt-thread
    │  │  └─zephyr
    │  ├─examples
    │  │  ├─anim
    │  │  ├─arduino
    │  │  │  └─LVGL_Arduino
    │  │  ├─assets
    │  │  │  ├─emoji
    │  │  │  └─font
    │  │  ├─event
    │  │  ├─get_started
    │  │  ├─layouts
    │  │  │  ├─flex
    │  │  │  └─grid
    │  │  ├─libs
    │  │  │  ├─bmp
    │  │  │  ├─ffmpeg
    │  │  │  ├─freetype
    │  │  │  ├─gif
    │  │  │  ├─png
    │  │  │  ├─qrcode
    │  │  │  ├─rlottie
    │  │  │  └─sjpg
    │  │  ├─others
    │  │  │  ├─fragment
    │  │  │  ├─gridnav
    │  │  │  ├─ime
    │  │  │  ├─imgfont
    │  │  │  ├─monkey
    │  │  │  ├─msg
    │  │  │  └─snapshot
    │  │  ├─porting
    │  │  ├─scroll
    │  │  ├─styles
    │  │  └─widgets
    │  │      ├─animimg
    │  │      ├─arc
    │  │      ├─bar
    │  │      ├─btn
    │  │      ├─btnmatrix
    │  │      ├─calendar
    │  │      ├─canvas
    │  │      ├─chart
    │  │      ├─checkbox
    │  │      ├─colorwheel
    │  │      ├─dropdown
    │  │      ├─img
    │  │      ├─imgbtn
    │  │      ├─keyboard
    │  │      ├─label
    │  │      ├─led
    │  │      ├─line
    │  │      ├─list
    │  │      ├─menu
    │  │      ├─meter
    │  │      ├─msgbox
    │  │      ├─obj
    │  │      ├─roller
    │  │      ├─slider
    │  │      ├─span
    │  │      ├─spinbox
    │  │      ├─spinner
    │  │      ├─switch
    │  │      ├─table
    │  │      ├─tabview
    │  │      ├─textarea
    │  │      ├─tileview
    │  │      └─win
    │  ├─scripts
    │  │  ├─built_in_font
    │  │  └─release
    │  ├─src
    │  │  ├─core
    │  │  ├─draw
    │  │  │  ├─arm2d
    │  │  │  ├─nxp
    │  │  │  │  ├─pxp
    │  │  │  │  └─vglite
    │  │  │  ├─sdl
    │  │  │  ├─stm32_dma2d
    │  │  │  ├─sw
    │  │  │  └─swm341_dma2d
    │  │  ├─font
    │  │  ├─hal
    │  │  ├─layouts
    │  │  │  ├─flex
    │  │  │  └─grid
    │  │  ├─libs
    │  │  │  ├─bmp
    │  │  │  ├─ffmpeg
    │  │  │  ├─freetype
    │  │  │  ├─fsdrv
    │  │  │  ├─gif
    │  │  │  ├─png
    │  │  │  ├─qrcode
    │  │  │  ├─rlottie
    │  │  │  └─sjpg
    │  │  ├─misc
    │  │  ├─others
    │  │  │  ├─fragment
    │  │  │  ├─gridnav
    │  │  │  ├─ime
    │  │  │  ├─imgfont
    │  │  │  ├─monkey
    │  │  │  ├─msg
    │  │  │  └─snapshot
    │  │  ├─themes
    │  │  │  ├─basic
    │  │  │  ├─default
    │  │  │  └─mono
    │  │  └─widgets
    │  │      ├─animimg
    │  │      ├─arc
    │  │      ├─bar
    │  │      ├─btn
    │  │      ├─btnmatrix
    │  │      ├─calendar
    │  │      ├─canvas
    │  │      ├─chart
    │  │      ├─checkbox
    │  │      ├─colorwheel
    │  │      ├─dropdown
    │  │      ├─img
    │  │      ├─imgbtn
    │  │      ├─keyboard
    │  │      ├─label
    │  │      ├─led
    │  │      ├─line
    │  │      ├─list
    │  │      ├─menu
    │  │      ├─meter
    │  │      ├─msgbox
    │  │      ├─objx_templ
    │  │      ├─roller
    │  │      ├─slider
    │  │      ├─span
    │  │      ├─spinbox
    │  │      ├─spinner
    │  │      ├─switch
    │  │      ├─table
    │  │      ├─tabview
    │  │      ├─textarea
    │  │      ├─tileview
    │  │      └─win
    │  └─tests
    │      ├─makefile
    │      ├─ref_imgs
    │      ├─src
    │      │  ├─test_cases
    │      │  ├─test_files
    │      │  └─test_fonts
    │      └─unity
    ├─lv_drivers
    │  ├─display
    │  ├─docs
    │  ├─gtkdrv
    │  ├─indev
    │  ├─sdl
    │  ├─wayland
    │  └─win32drv
    └─smartClass
        ├─include
        ├─res
        │  ├─music
        │  ├─pic
        │  ├─text
        │  └─video
        └─src
        
### linux_aitalk:
运行（在 linux_aitalk/sample/asr_offline/下）64bit_make.sh

### lvgl_arm:
运行（在lvgl_arm/下）make

语言：C/C++
调用三方：LVGL、科大讯飞的SDK



