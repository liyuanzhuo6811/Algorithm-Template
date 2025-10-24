import requests, json, time, os
con = open("work/tex/cont.tex", "w", encoding="utf8")
con.write("\\section{贡献者}\n感谢所有为本项目贡献过提交的成员。\n")
reg = requests.get("https://api.github.com/repos/liyuanzhuo6811/Algorithm-Template/contributors", verify=False)
if reg.status_code != 200:
    print("Cannot get the list.")
    exit(1)
head = {
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
    "Accept-Encoding": "gzip, deflate, br, zstd",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6",
    "Cache-Control": "no-cache",
    "Connection": "keep-alive",
    "Host": "avatars.githubusercontent.com",
    "Pragma": "no-cache",
    "Sec-Fetch-Dest": "document",
    "Sec-Fetch-Mode": "navigate",
    "Sec-Fetch-Site": "none",
    "Sec-Fetch-User": "?1",
    "Upgrade-Insecure-Requests": "1",
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/140.0.0.0 Safari/537.36 Edg/140.0.0.0",
    "sec-ch-ua": "\"Chromium\";v=\"140\", \"Not=A?Brand\";v=\"24\", \"Microsoft Edge\";v=\"140\"",
    "sec-ch-ua-mobile": "?0",
    "sec-ch-ua-platform": "\"Windows\""
}
p = json.loads(reg.text)
image_suffix = {
    102 : "bmp",
    104 : "gif",
    255 : "jpg",
    137 : "png",
    104 : "png",
    0   : "heic",
    111 : "tif"
}
def gen(username, userid, conts, suf):
    return f"""\\begin{{figure}}[!htpb]
\\begin{{minipage}}{{0.1\\textwidth}}
\\includegraphics[width=\\textwidth]{{images/{userid}.{suf}}}
\\end{{minipage}}
\\hfill
\\begin{{minipage}}{{0.8\\textwidth}}
\\textbf{{{username} 贡献了 {conts} 次提交}}
\\end{{minipage}}
\\end{{figure}}
"""
for prs in p:
    print(prs)
    print(prs["login"], prs["avatar_url"])
    img = requests.get(prs["avatar_url"], headers=head, timeout=5, verify=False)
    suf = image_suffix.get(img.content[0], "jpg")
    avt_path = f"work/tex/images/{prs["id"]}.{suf}"
    print(avt_path)
    avt = open(avt_path, "wb")
    avt.write(img.content)
    avt.close()
    os.system(f"bitmap2pp -l eps.image {avt_path}")
    con.write(gen(prs["login"], prs["id"], prs["contributions"], suf))
    time.sleep(1)