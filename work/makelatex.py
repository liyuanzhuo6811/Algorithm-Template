import os
print(os.getcwd())
titf = ["chapter", "section", "subsection", "subsubsection", "paragraph", "subparagraph"]
tex = open("work\\temp1\\test.tex", "w", encoding="utf8")
tex.write("""\\documentclass[9pt, a4paper, oneside]{book}
\\usepackage{ctex}
\\usepackage{authblk}
\\usepackage{listings}
\\usepackage{color}
\\usepackage{geometry}
\\usepackage{titlesec}

\\titleformat{\\chapter}
{\\normalfont\\Large\\bfseries}{第 \\thechapter 部分}{1em}{}

\\titleformat{\\section}
{\\normalfont\\Large\\bfseries}{\\thesection}{1em}{}

\\titleformat{\\subsection}
{\\normalfont\\large\\bfseries}{\\thesubsection}{1em}{}

\\titleformat{\\subsubsection}
{\\normalfont\\normalsize\\bfseries}{\\thesubsubsection}{1em}{}
\\geometry{left=3.18cm, right=3.18cm, top=2.54cm, bottom=2.54cm}
\\title{\\Huge XCPC Template Library}
\\author{
    Wu Honglin / real01bit \\\\
    Li Yuanzhuo / SnowFlavour \\\\
    Liu Haocheng / lotus\\_grass \\\\
}
\\date{最后一次修改：\\today}
\\newfontfamily\\firacode{FiraCode-Regular.ttf}
\\lstset{
    language=C++,
    basicstyle=\\firacode\\small,
    breaklines=true,
    keywordstyle=\\bfseries\\color{red},
    stringstyle=\\color{green}\\ttfamily,
    morekeywords={},
    emph={self},
    emphstyle=\\bfseries,
    commentstyle=\\itshape,
    stringstyle=\\bfseries,
    columns=flexible,
    numbers=left,
    numbersep=2em,
    numberstyle=\\footnotesize,
    frame=topline,
    framesep=1em
}
\\begin{document}
\\maketitle
\\tableofcontents
""")

# exit(0)
def gci(filepath, rootpath):
    files = os.listdir(filepath)
    if ".makelatex-ignore" in files or ".git" in filepath or ".vscode" in filepath:
        return
    print(filepath)
    totc = list(rootpath).count("\\")
    nowc = list(filepath).count("\\")
    # print(totc, nowc)
    # print(nowc - totc)
    # print(fi)
    red = filepath.split("\\")[-1]
    if nowc > totc:
        tex.write(f"\\{titf[nowc - totc - 1]}{{{red}}}\n")

    for fi in files:
        fi_d = os.path.join(filepath, fi)
        if os.path.isdir(fi_d):
            gci(fi_d, rootpath)
    for fi in files:
        fi_d = os.path.join(filepath, fi)
        if not os.path.isdir(fi_d):
            if fi_d[-4:] == ".cpp":
                tex.write(f"\\{titf[nowc - totc]}{{{fi.replace("_", "\\_")}}}\n")
                with open(fi_d, encoding="utf8") as tmp:
                    code = tmp.read()
                    tex.write("\\begin{lstlisting}[language={C++}]\n")
                    tex.write(code)
                    tex.write("\\end{lstlisting}\n")

gci(os.getcwd(), os.getcwd())
tex.write("\\end{document}")
