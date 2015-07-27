"""""""""""""""""""""""""""""""""""""""""""""""""
"显示
"""""""""""""""""""""""""""""""""""""""""""""""""
syntax on								"语法高亮
autocmd InsertLeave * se nocul			"用浅色高亮当前行
autocmd InsertEnter * se nocul			"用浅色高亮当前行(cul带下划线)
set number								"行号
set ruler								"显示标尺
set confirm								"处理未保存或只读文件是弹出确认
set autoread							"文件改变时，自动载入
"set nobackup							"无备份
set autowrite
"set cursorline							"突出显示当前行(下划线)
set foldenable							"允许折叠
set foldmethod=manual					"手动折叠
set foldcolumn=0
set foldlevel=3
"set background=dark					"黑色背景
set nocompatible						"去掉vi一致性模式
"set lines=40 columns=155				"设置窗口大小
set magic
set clipboard+=unnamed					"共享剪贴板
"colorscheme=murphy						"配色方案
"colorscheme=torte						"配色方案
"colorscheme=desert						"配色方案
"colorscheme=elflord					"配色方案
"colorscheme=ron						"配色方案
"""字符编码"""
"set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
"set enc=utf-8
"set termencoding=utf-8
"set encoding=utf-8
"set fileencodings=utf-8,ucs-bom,cp936
"set fileencoding=utf-8
"""语言"""
set helplang=cn
set langmenu=zh_CN.UTF-8
set showcmd								"显示输入的命令
set cmdheight=1							"命令行高度为1
set laststatus=1						"启动显示状态行(1),总是显示(2)
"""缩进"""
set autoindent
set cindent
set smartindent
""""tab"""
set tabstop=4							"tabs键宽度为4
set softtabstop=4						"统一缩进为4
set shiftwidth=4			
set noexpandtab							"不使用空格代替tab
set smarttab							"在行和段开始处使用tab
"""gui设置"""
set guioptions-=T						"隐藏工具栏
set guioptions-=m						"隐藏菜单栏
set guifont=Courier_New:h10:cANSI		"设置字体
filetype on								"侦测文件类型
filetype plugin on						"侦测文件类型插件
filetype indent on						"侦测文件类型缩进配置
"set viminfo+=!							"保存全局变量
set linespace=0							"字符见插入像素数目
set wildmenu							"增强模式中的命令行自动完成操作
set backspace=2							"是回车正常处理indet,eol,start等
set mouse=a
set selection=exclusive
set selectmode=mouse,key
set showmatch							"高亮显示匹配的括号
set matchtime=1							"匹配括号高亮时间(单位0.1s)
set ignorecase							"搜索忽略大小写
"set hlsearch							"搜索字符高亮
set incsearch
set gdefault							"行内替换
"""""""""""""""""""""""""""""""""""""""""""""""""
"默认代码
"""""""""""""""""""""""""""""""""""""""""""""""""
autocmd BufNewFile *.cpp,*.[ch],*.sh,*.java exec ":call DefaultCode()"
func DefaultCode()
	if &filetype == 'sh'
		call setline(1, "\#!/bin/bash")
		call append(line("."), "")
	endif
	if &filetype == 'cpp'
		exec ":r ~/E/acm/template.cpp"
		exec ":1d"
		exec ":$-10"
		exec ":normal zz"
	elseif &filetype == 'c'
		call append(line(".")+4, "#include <stdio.h>")
		call append(line(".")+5, "")
	endif
endfunc
"""""""""""""""""""""""""""""""""""""""""""""""""
"自动补全
"""""""""""""""""""""""""""""""""""""""""""""""""
":inoremap ( ()<ESC>i
":inoremap ) <c-r>=ClosePair(')')<CR>
":inoremap [ []<ESC>i
":inoremap ] <c-r>=ClosePair(']')<cr>
":inoremap { {<CR>}<ESC><s-o>
":inoremap " ""<ESC>i
":inoremap ' ''<ESC>i
func ClosePair(char)
	if getline('.')[col('.') - 1] == a:char
			return "\<Right>"
	else
		return a:char
	endif
endfunc
set completeopt=longest,menu
"""""""""""""""""""""""""""""""""""""""""""""""""
"键盘
"""""""""""""""""""""""""""""""""""""""""""""""""
"nmap <leader>w :w!<cr>
"nmap <leader>f :find<cr>
""全选+复制 Ctrl+A
map <C-a> ggVG"+y
map! <C-a> <Esc> ggVG"+Y
map <F12> gg=G
"选中状态下 复制 Ctrl+c
vmap <C-c> "+y
"去空行
nnoremap <F2> :g/^\s*$/d<cr>
"比较文件
"nnoremap <C-F2> :vert diffsplit
"新建标签
"map <M-F2> :tabnew<CR>
"列出当前目录文件
"map <F3> :tabnew .<CR>
"打开树状文件目录
"map <C-F3> \be
""C,C++ 编译运行
map <F5> :call Compile()<CR>
imap <F5> <ESC> :call Compile()<CR>
func Compile()
	exec "w"
	if &filetype == 'c'
		exec "!g++ % -o %< -DACM_TEST"
		"exec "!./%<"
	elseif &filetype == 'cpp'
		exec "!g++ % -o %< -DACM_TEST"
		"exec "!./%<"
	elseif &filetype == 'java'
		exec "!javac %"
		"exec "!java %<"
	endif
endfunc
"run with inputfile
map <C-F5> :!./%< < in.txt<cr>
"run
map <C-r> :call Run() <cr>
func Run()
	if &filetype == 'java'
		exec ":!java %<"
	elseif &filetype == 'cpp'
		exec ":!./%<"
	elseif &filetype == 'c'
		exec ":./%<"
	endif
endfunc
"edit in
map <F3> :!vim in.txt <cr>
""C,C++ 调试
map <F8> :call Rungdb()<CR>
func Rungdb()
	exec "w"
	exec "!g++ % -g -o %<"
	exec "!gdb ./%<"
endfunc
"保存
map <F2> :w  <cr>
imap <F2> <esc>:w <cr>
