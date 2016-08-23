set nocompatible              " be iMproved, required
syntax on
"filetype off                  " required

" auto vimrc								"%.. 
autocmd! BufWritePost $HOME/.vimrc source ~/.vimrc 
"syntastic
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

"let g:syntastic_always_populate_loc_list = 1
"let g:syntastic_auto_loc_list = 1
"let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 1
"colorscheme monokai
"match #!/user/bin/...
autocmd FileType sh,python,perl syntax match itptType "^[#][!][/].\+$"
autocmd FileType sh,python,perl hi itptType ctermfg=5 cterm=italic
"hi itptType ctermfg=6 cterm=bold
"YCM
let g:ycm_autoclose_preview_window_after_completion = 1
let g:syntastic_enable_perl_checker = 1
autocmd FileType php,java,ruby,python,c,perl,html,css,xml,shell,bash,zsh,text,vim let g:EclimCompletionMethod = 'omnifunc'
set hlsearch
set nu
set tabstop=4
set shiftwidth=4
map <CR> :nohl <CR>
let g:Powerline_symbols = 'fancy'
set encoding=utf-8
set smartindent 
" my style with zsh
highlight Comment ctermfg=black cterm=bold
highlight LineNr ctermfg=6 cterm=italic 
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
