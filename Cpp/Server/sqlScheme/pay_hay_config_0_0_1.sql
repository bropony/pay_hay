/*
Navicat MySQL Data Transfer

Source Server         : old_ver_192.168.3.238
Source Server Version : 50152
Source Host           : 192.168.3.238:3306
Source Database       : pay_hay_config_0_0_1

Target Server Type    : MYSQL
Target Server Version : 50152
File Encoding         : 65001

Date: 2015-03-14 10:00:03
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `t_error_code`
-- ----------------------------
DROP TABLE IF EXISTS `t_error_code`;
CREATE TABLE `t_error_code` (
  `error_code` int(11) NOT NULL AUTO_INCREMENT COMMENT '错误码',
  `error_name` varchar(60) NOT NULL DEFAULT '' COMMENT '错误名',
  `error_str` varchar(100) NOT NULL DEFAULT '' COMMENT '错误描述',
  PRIMARY KEY (`error_code`),
  UNIQUE KEY `AK_Identifier_2` (`error_name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=20005 DEFAULT CHARSET=utf8 COMMENT='错误码  [开发人员专用]';

-- ----------------------------
-- Records of t_error_code
-- ----------------------------
INSERT INTO `t_error_code` VALUES ('10000', 'ExceptionCodeUnkown', '未知错误');
INSERT INTO `t_error_code` VALUES ('10001', 'Error_invalidOperation', '无效操作');
INSERT INTO `t_error_code` VALUES ('10002', 'ExceptionBadJsData', '数据出错');
INSERT INTO `t_error_code` VALUES ('10003', 'Error_nullUserPtr', '请先登录或注册');
INSERT INTO `t_error_code` VALUES ('10004', 'Error_SerializeError', '序列化错误');
INSERT INTO `t_error_code` VALUES ('10005', 'Error_NotRegisterdRmiCall', '未注册的远程方法调用');
INSERT INTO `t_error_code` VALUES ('20001', 'Error_accountOrPasswd', '账号或者密码错误');
INSERT INTO `t_error_code` VALUES ('20002', 'Error_accountExisted', '账号已存在');
INSERT INTO `t_error_code` VALUES ('20003', 'Error_nicknameUsed', '昵称已被使用');
INSERT INTO `t_error_code` VALUES ('20004', 'Error_userDataError', '用户数据有错，请重新登录');

-- ----------------------------
-- Table structure for `t_event_config`
-- ----------------------------
DROP TABLE IF EXISTS `t_event_config`;
CREATE TABLE `t_event_config` (
  `event_id` int(11) NOT NULL DEFAULT '0' COMMENT '事件id',
  `event` varchar(128) NOT NULL DEFAULT '' COMMENT '作操名称',
  `in_params` varchar(1024) NOT NULL DEFAULT '' COMMENT '{"key":"type", "key":"type",...}',
  `out_params` varchar(1024) NOT NULL DEFAULT '' COMMENT '{"key":"type", "key":"type", ...}',
  PRIMARY KEY (`event_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_event_config
-- ----------------------------
INSERT INTO `t_event_config` VALUES ('12', 'test', 'dt:date', 'testOut:date');
INSERT INTO `t_event_config` VALUES ('13', 'showError', 'dt:date', 'out:string');
INSERT INTO `t_event_config` VALUES ('14', 'uploadImage', 'img:image', 'fileName:string');
INSERT INTO `t_event_config` VALUES ('15', 'echo', 'input:STest', 'output:STest');

-- ----------------------------
-- Table structure for `t_struct_config`
-- ----------------------------
DROP TABLE IF EXISTS `t_struct_config`;
CREATE TABLE `t_struct_config` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `name` varchar(128) NOT NULL DEFAULT '' COMMENT '结构体名称',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '类型。1--struct 2--list 3--enum',
  `fields` varchar(2048) NOT NULL DEFAULT '' COMMENT '字段定义 name:type#name:type#...',
  `descr` varchar(2048) NOT NULL DEFAULT '' COMMENT '描述',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_struct_config
-- ----------------------------
INSERT INTO `t_struct_config` VALUES ('1', 'SeqShort', '2', 'short', '');
INSERT INTO `t_struct_config` VALUES ('2', 'SeqLong', '2', 'long', '');
INSERT INTO `t_struct_config` VALUES ('3', 'SeqInt', '2', 'int', '');
INSERT INTO `t_struct_config` VALUES ('4', 'SeqBool', '2', 'bool', '');
INSERT INTO `t_struct_config` VALUES ('5', 'SeqString', '2', 'string', '');
INSERT INTO `t_struct_config` VALUES ('6', 'STest', '1', 's:SeqShort#l:SeqLong#i:SeqInt#b:SeqBool#ss:SeqString', '');
INSERT INTO `t_struct_config` VALUES ('7', 'SeqSeqInt', '2', 'SeqInt', '');
INSERT INTO `t_struct_config` VALUES ('8', 'SGoo', '1', 'st:STest#ilist:SeqSeqInt', '');
