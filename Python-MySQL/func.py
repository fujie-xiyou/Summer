#!/usr/bin/env python
# coding=utf-8
import pymysql
EveryPage = 10
db=pymysql.connect(host = "fujie.bid",user = "credit",passwd = "lllc",database = 'credit',charset = 'utf8')
cur=db.cursor()
def GetUid(StudentNum) :
    cur.execute("SELECT uid FROM users WHERE StudentNum = %s" % StudentNum)
    res=cur.fetchall()
    if len(res)==0 :
        return -1
    else :
        return res[0][0];
def GetPw(uid) :
    cur.execute("SELECT pw FROM users WHERE uid = %d" % uid)
    return cur.fetchall()[0][0]
def GetUserInfo(uid) :
    cur.execute("SELECT * FROM user WHERE uid = %d" % uid)
    return cur.fetchall()[0]
def GetActivityNow(page) :
    cur.execute("SELECT * FROM activity WHERE curdate() >= date_start AND curdate() <= date_end LIMIT %d,%d" % ((page-1)*EveryPage,EveryPage))
    return cur.fetchall()
def GetActivityFuture(page) :
    cur.execute("SELECT * FROM activity WHERE curdate() < data_start LIMIT %d,%d" % ((page-1)*EveryPage,EveryPage))
    return cur.fetchall()
def GetActivityStatus(uid,aid) :
    cur.execute("SELECT state FROM record WHERE uid = %d AND aid = %d" %(uid ,aid))
    res=cur.fetchall()
    if len(res) == 0 :
        return -1;
    else :
        return res[0][0]
def ChangeInfo(uid,pw,phone) :
    return cur.execute("UPDATE users SET pw = %d phone = %s WHERE uid = %d" % (pw,phone,uid))
def GetRecordStatus(uid,page) :
    cur.execute("SELECT * FROM record WHERE uid = %d LIMIT %d,%d" % (uid,(page-1)*EveryPage,EveryPage))
    return cur.fetchall()
def GetRecordShow(page) :
    cur.execute("SELECT * FROM record WHERE state <> 0 LIMIT %d,%d" % ((page - 1)*EveryPage,EveryPage))
    return cur.fetchall()

