CREATE DATABASE credit CHARACTER SET utf8;
USE credit;
CREATE TABLE users (
    uid int NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键,自增',
    StudentNum char(8) COMMENT '学号',
    name text COMMENT '姓名',
    per tinyint COMMENT '权限(0为普通用户,1为管理员)',
    class text COMMENT '班级',
    phone text COMMENT '电话',
    pw text COMMENT '密码',
    score float COMMENT '已获得学分'
    )COMMENT='存放用户信息';


CREATE TABLE record (
    rid int NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键,自增',
    uid char(8) COMMENT '对应users表中uid',
    aid int COMMENT '对应activity表中aid',
    state int COMMENT '状态(0为待审核,1为已通过.2为被驳回)',
    date datetime COMMENT '申请时间'
    )COMMENT='存放学分申请记录';


CREATE TABLE activity (
    aid int NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键,自增',
    score1 float COMMENT '组织者/获奖者学分',
    score2 float COMMENT '参与者学分',
    type text COMMENT '所属类别',
    college text COMMENT '所属学院',
    title text COMMENT '活动标题',
    content text COMMENT '活动内容',
    date_local text COMMENT '活动举办时间/地点',
    date_start date COMMENT '学分申请开始时间',
    date_end date COMMENT '学分申请截止时间',
    sponsor text COMMENT '主办单位',
    head text COMMENT '负责人'
    )COMMENT='存放学分项目';
