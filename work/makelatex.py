import os
print(os.getcwd())
tex = open("temp1/test.tex", "w")
tex.write("""\documentclass[12pt, a4paper]{book}
\usepackage{ctex}
\usepackage{authblk}
\usepackage{listings}
\usepackage{color}
\usepackage{geometry}
\usepackage{titlesec}

\titleformat{\chapter}
{\normalfont\Large\bfseries}{第 \thechapter 部分}{1em}{}

\titleformat{\section}
{\normalfont\Large\bfseries}{\thesection}{1em}{}

\titleformat{\subsection}
{\normalfont\large\bfseries}{\thesubsection}{1em}{}

\titleformat{\subsubsection}
{\normalfont\normalsize\bfseries}{\thesubsubsection}{1em}{}
\geometry{left=3.18cm, right=3.18cm, top=2.54cm, bottom=2.54cm}
\title{\Huge XCPC Template Library}
\author{
    Wu Honglin / real01bit \\
    Li Yuanzhuo / SnowFlavour \\
    Liu Haocheng / lotus\_grass \\
}
\date{最后一次修改：\today}
\newfontfamily\firacode{FiraCode-Regular.ttf}
\lstset{
    language=C++,
    basicstyle=\firacode,
    breaklines=true,
    keywordstyle=\bfseries\color{red},
    stringstyle=\color{green}\ttfamily,
    morekeywords={},
    emph={self},
    emphstyle=\bfseries,
    commentstyle=\itshape,
    stringstyle=\bfseries,
    columns=flexible,
    numbers=left,
    numbersep=2em,
    numberstyle=\footnotesize,
    frame=topline,
    framesep=1em
}
\begin{document}
\maketitle
""")
for dirpath, dirnames, filenames in os.walk(os.getcwd()):
    print("当前目录：", dirpath)
    tex.write(f"\\chapter\{{{dirpath}}}\n")
    for file in filenames:
        if ".cpp" in file:
            if file[-4:] == ".cpp":
                print(f"Working:{dirpath}/{file}")
                
