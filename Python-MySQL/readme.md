### 数据库操作函数说明
```
int GetUid(String StudentNum)
    传入学号(string) 如果学号存在则返回对应uid(int) 否则返回-1
```
```
String GetPw(int uid)
    传入uid(int) 返回对应的密码字段(String)
```
```
Tuple GetUserInfo(int uid)
    返回uid对应的用户信息(Tuple) 返回结果: (uid,'学号','姓名',权限(0/1),'班级','电话','密码'.已获得学分)
```
```
Tuple GetActivityNow(int page)
    传入需要返回的页码(默认每页10条内容)，返回一个二维元组，包含当前正在进行的学分项目
```
```
Tuple GetActivityFuture(int page) :
    参考上一条
```
```
int  GetActivityStatus(int uid,int aid)
    用于判断某一活动对应某一用户的状态 返回-1表示未申请,返回0/1/2分别表示 待审核/已通过/被驳回
    该函数可用于区别在对与某一条正在开放申请的活动底部显示的按钮 如: 该显示 '申请学分' 或者是 '已申请过'
    (甚至可以直接在此处展示 '我要申诉' 按钮)
```
```
bool ChengeInfo(int uid,String phone,String pw)
    用于修改电话和密码，其他信息不应该允许修改！
```
```
Tuple GetRecordStatus(int uid,int page)
    返回一个二维元组  包含uid对应的用户的学分申请记录 
```
```
Tuple GetRecordShow(int page)
    返回一个二维元组  包含所有已处理(尚未处理的申请记录将不在此展示)的学分申请记录(state字段为1表示通过 为2表示驳回)
```
