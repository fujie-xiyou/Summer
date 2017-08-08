#!/usr/bin/env pythonmZ# coding=utf-8
import pymysql
db=pymysql.connect(host = "sql.fujie.bid",user = "root",passwd = "AAA00aaa",database = 'acm',charset = 'utf8')
cur=db.cursor()
str = raw_input()
word = ""
for i in str:
    if 'a' <= i <= 'a' :
        word = word + i
    elif 'A' <= i <= 'Z':
        word = word + (i+32)
    else :
        if count(word) > 0 :
            cur.execute("INSERT INTO word VALUES('%s')" % word)
            word = ""

cur.execute("SELECT DISTINCT word FROM word ORDER BY word")
rec = cur.fetchall()
for i in rec:
    print("%s\n" % i)

cur.execute("DELETE FROM word")
db.close()

