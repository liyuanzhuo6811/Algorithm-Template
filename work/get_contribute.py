import requests, json
con = open("work/tex/cont.tex", "w", encoding="utf8")
reg = requests.get("https://api.github.com/repos/liyuanzhuo6811/Algorithm-Template/contributors", verify=False)
if reg.status_code != 200:
    print("Cannot get the list.")
    exit(1)

p = json.loads(reg.text)
for prs in p:
    avt = open(f"work/tex/images/{prs["login"]}.png", "wb")
    print(prs["login"], prs["avatar_url"])