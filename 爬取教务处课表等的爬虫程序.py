import requests
from bs4 import BeautifulSoup
import re
import json

dat=requests.get("替换成自己的教务系统网站（后同）").headers['Set-Cookie']
cookie=dat[:-8]

header={"User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:34.0) Gecko/20100101 Firefox/34.0"
        ,"Cookie": cookie
        ,"Referer": "http://202.115.47.141/login"
        }

img=requests.get("http://202.115.47.141/img/captcha.jpg",headers=header).content
with open("cap.jpg","wb") as f:
    f.write(img)

yz=input("输入验证码：")
para = {"j_username" :"替换自己学号",
        "j_password": "替换自己密码",
        "j_captcha": yz}

respon=requests.post("http://202.115.47.141/j_spring_security_check",data=para,headers=header)
print(respon.url)
data=requests.get('http://zhjw.scu.edu.cn/student/courseSelect/thisSemesterCurriculum/ajaxStudentSchedule/callback',headers=header)
with open('class.txt','w') as f:
   f.write(data.text)
print('登录成功！开始抓取课表')

with open("index.json","w") as f:
    json.dump(data.json(),f,ensure_ascii=False)
f.close()
print('课表抓取成功，开始输出课表')
print('所有课程信息如下:')
with open('index.json','r') as f:
  tem=json.load(f)
js=json.dumps(tem,indent=4,separators=(',',':'),ensure_ascii=False)
print(js)

with open('tem.txt','w') as f:
    f.write(js)
