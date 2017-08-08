#!/usr/bin/env python
# coding=utf-8
import pymysql
db=pymysql.connect("120.78.96.152","root","AAA000aaa", "acm")
cur=db.cursor()
str = input()
word = ""
for i in str:
    if 'a' <= i <= 'z' :
        word = word + i
    elif 'A' <= i <= 'Z':
        word = word + (i+32)
    else :
        if len(word) > 0 :
            try :
                print(cur.execute("INSERT INTO word VALUES('%s')" , word))
            except :
                db.rollback()
            word = ""
cur.execute("SELECT DISTINCT word FROM word ORDER BY word")
rec = cur.fetchall()
#for i in rec:
 #   print("%s" % i)
print(rec)
#cur.execute("DELETE FROM word")
db.close()

