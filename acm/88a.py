#!/usr/bin/env python
# coding=utf-8
import pymysql
import sys
db=pymysql.connect("sql.fujie.bid","root","AAA000aaa", "acm")
cur=db.cursor()
str = ""
while True:
    try :
        str = str + input() + "\n"
    except :
        break
word = ""
for i in str:
    if 'a' <= i <= 'z' :
        word = word + i
    elif 'A' <= i <= 'Z':
        word = word + i.lower()
    else :
        if len(word) > 0 :
            cur.execute("INSERT INTO word VALUES('%s')" % word)
            word = ""
cur.execute("SELECT DISTINCT word FROM word ORDER BY word")
rec = cur.fetchall()
for i in rec:
    print("%s" % i)
cur.execute("DELETE FROM word")
db.close()

