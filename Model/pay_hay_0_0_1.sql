/*
Navicat MySQL Data Transfer

Source Server         : zkoding
Source Server Version : 50623
Source Host           : 112.74.102.141:3306
Source Database       : pay_hay_0_0_1

Target Server Type    : MYSQL
Target Server Version : 50623
File Encoding         : 65001

Date: 2015-06-23 14:47:38
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `t_user`
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'userId',
  `account` varchar(128) NOT NULL DEFAULT '',
  `nickname` varchar(128) NOT NULL DEFAULT '',
  `login_key` varchar(128) NOT NULL DEFAULT '',
  `avatar` int(11) NOT NULL DEFAULT '0' COMMENT 'avatar img id',
  `create_dt` datetime NOT NULL DEFAULT '2015-01-01 00:00:00',
  PRIMARY KEY (`user_id`),
  KEY `idx_account` (`account`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_user
-- ----------------------------
INSERT INTO `t_user` VALUES ('1', 'goodboy', 'goodboy', '824e02af6cea9dcb4593bcc301bee4e0', '42', '2015-04-16 20:50:28');
INSERT INTO `t_user` VALUES ('2', 'ljyi1986', '小朋友', 'cbdbb52b3b86c951f3c6f8d9d023d7bd', '0', '2015-04-17 00:17:01');
INSERT INTO `t_user` VALUES ('3', 'Johnson', 'Johnson', '5ff25f82a7ca9c59b6ef5713f830dd87', '0', '2015-04-17 10:04:50');
INSERT INTO `t_user` VALUES ('4', 'Wendy', 'Wendy', '6954d5392dbcde76c19260f3b1a13380', '45', '2015-04-18 12:09:27');
INSERT INTO `t_user` VALUES ('5', 'allen', 'wen\n\n\n\n\nallen', '6954d5392dbcde76c19260f3b1a13380', '20', '2015-05-16 16:48:03');
INSERT INTO `t_user` VALUES ('6', 'ljyi1', '德门', 'cbdbb52b3b86c951f3c6f8d9d023d7bd', '23', '2015-05-16 23:25:34');
INSERT INTO `t_user` VALUES ('7', 'linjiayi', '八尺天玄', 'cbdbb52b3b86c951f3c6f8d9d023d7bd', '0', '2015-06-02 23:14:35');
INSERT INTO `t_user` VALUES ('8', 'linjiay8', 'kajzbs', '43b71e144186fe2c7730b6f64f8eba82', '0', '2015-06-06 15:25:07');
INSERT INTO `t_user` VALUES ('9', '3646464679799', '感慨', 'aee26cc1348da4722923a8fb40b4f6ef', '47', '2015-06-15 00:08:15');

-- ----------------------------
-- Table structure for `t_user_comment`
-- ----------------------------
DROP TABLE IF EXISTS `t_user_comment`;
CREATE TABLE `t_user_comment` (
  `comment_id` int(11) NOT NULL AUTO_INCREMENT,
  `post_id` int(11) NOT NULL DEFAULT '0',
  `from_user_id` int(11) NOT NULL DEFAULT '0',
  `from_nickname` varchar(128) NOT NULL DEFAULT '',
  `content` varchar(1024) NOT NULL DEFAULT '',
  `comment_dt` datetime NOT NULL DEFAULT '2015-01-01 00:00:00',
  PRIMARY KEY (`comment_id`),
  KEY `idx_post_id` (`post_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_user_comment
-- ----------------------------
INSERT INTO `t_user_comment` VALUES ('1', '13', '4', 'Wendy', '', '2015-04-28 22:20:33');
INSERT INTO `t_user_comment` VALUES ('2', '12', '4', 'Wendy', '', '2015-05-09 17:15:06');
INSERT INTO `t_user_comment` VALUES ('3', '11', '4', 'Wendy', '', '2015-05-09 17:15:40');
INSERT INTO `t_user_comment` VALUES ('4', '14', '5', 'wen\n\n\n\n\nallen', '塔斯肯', '2015-05-16 16:58:34');
INSERT INTO `t_user_comment` VALUES ('5', '15', '4', 'Wendy', '第一把', '2015-05-17 10:05:20');
INSERT INTO `t_user_comment` VALUES ('6', '18', '7', '八尺天玄', '不错啊\n', '2015-06-02 23:20:07');
INSERT INTO `t_user_comment` VALUES ('7', '21', '4', 'Wendy', '为啥是这样的效果', '2015-06-06 10:39:16');
INSERT INTO `t_user_comment` VALUES ('8', '31', '4', 'Wendy', '听说很漂亮', '2015-06-06 21:38:52');
INSERT INTO `t_user_comment` VALUES ('9', '30', '4', 'Wendy', 'said something', '2015-06-14 22:49:48');

-- ----------------------------
-- Table structure for `t_user_img`
-- ----------------------------
DROP TABLE IF EXISTS `t_user_img`;
CREATE TABLE `t_user_img` (
  `img_id` int(11) NOT NULL AUTO_INCREMENT,
  `img_path` varchar(1024) NOT NULL DEFAULT '',
  `short_desc` varchar(512) NOT NULL DEFAULT '',
  PRIMARY KEY (`img_id`),
  KEY `idx_img_id` (`img_id`)
) ENGINE=InnoDB AUTO_INCREMENT=50 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_user_img
-- ----------------------------
INSERT INTO `t_user_img` VALUES ('1', '20150416//3adbbc79-860c-49c0-aab0-f3ec933d95a9.png', 'Web Image');
INSERT INTO `t_user_img` VALUES ('2', '20150416//6fbf86a6-f6cf-409d-9b41-3d7c557d0f2c.jpg', 'Web Image');
INSERT INTO `t_user_img` VALUES ('3', '20150416//c8cfcd8f-1b33-4b7f-be44-877c38e1a56b.jpg', 'avatar');
INSERT INTO `t_user_img` VALUES ('4', '20150416//0fa1886e-5583-4f15-bcf8-937a994d4fe8.jpg', 'Web Image');
INSERT INTO `t_user_img` VALUES ('5', '20150416//2023d750-9766-4fd9-9d6f-40efb2aaec72.jpg', 'Web Image');
INSERT INTO `t_user_img` VALUES ('6', '20150417//8f8e8ed2-7d11-4bab-af23-08b3dd3262b9.jpg', 'Web Image');
INSERT INTO `t_user_img` VALUES ('7', '20150418//eea20737-fe20-43d2-bad3-010bc8b015f4.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('8', '20150418//3786b893-4fa4-4fde-b7ab-5550c7165c6e.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('9', '20150418//57f4b231-bd1c-48bc-8a4d-108bff2e528c.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('10', '20150418//9e8bfe51-850c-4f8b-928a-c1443b615713.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('11', '20150419//0fd8bbf6-848f-4937-a1c7-142ebf3e612e.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('12', '20150419//d35ea9e6-9703-4851-9a3c-b11950741790.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('13', '20150419//64b9d6b9-9a9a-4079-996e-d8c5bc88012f.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('14', '20150419//f04a8bdb-80c9-4196-a0e5-af7c53959ad2.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('15', '20150419//f7d7547d-992b-4c1c-b8d8-966aaa74bed4.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('16', '20150419//f0f2843f-c1b3-423a-8750-24d9aed3ae41.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('17', '20150419//7751e819-228a-466a-a0fb-6e2ecc402066.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('18', '20150421//3631213b-c5eb-4fff-93ea-8181cb4d1d0b.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('19', '20150421//2ec1c685-dd6a-4ed1-9c86-43155f6b967f.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('20', '20150516//3d15750b-5ff8-47e1-a36a-77e5be2718d0.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('21', '20150516//9db3d93d-97fe-415c-8ddd-dc429d096f6c.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('22', '20150516//d966972d-a6c3-4cd7-a251-0bb4f80f5aef.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('23', '20150516//f894d816-5fe8-4556-a8bf-e1ad1fb59d7a.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('24', '20150525//6357a092-6fa5-4c48-a209-162cde61a910.png', 'Web Image');
INSERT INTO `t_user_img` VALUES ('25', '20150525//17d0d6ce-f2f6-4738-9866-6d41c0094613.jpg', 'Web Image');
INSERT INTO `t_user_img` VALUES ('26', '20150525//a553985e-1092-4925-84ec-d82ce3db35cf.jpg', 'Web Image');
INSERT INTO `t_user_img` VALUES ('27', '20150602//efce86f5-4ab9-41f2-adba-1a79a98d7074.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('28', '20150602//57fabfa6-a44b-4763-b27f-170453acba4e.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('29', '20150602//44765abe-80bc-4841-81ef-81a1ac57b561.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('30', '20150606//47a289d0-336f-4236-a376-10592fd69cdd.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('31', '20150606//f735ef21-a882-4937-b2ea-22faf37e9a99.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('32', '20150606//2e5aca3c-fcce-4c09-8fce-e5f47ec04e5a.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('33', '20150606//fd6b210c-27ce-4be7-9c8e-30b32c83bb4f.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('34', '20150606//770d73cb-1caa-4c9f-8b58-8efff02a7ec0.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('35', '20150606//76464fb3-182c-4879-be28-9f312cb471ea.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('36', '20150606//59e8bd66-bee9-434e-9c79-02055f6494e3.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('37', '20150606//b1f8ed0d-b019-4f8f-81ea-7218e6f8f75d.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('38', '20150606//014046c0-3795-4cbc-8445-bfedf0afab6d.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('39', '20150606//2c265d03-96ee-47fa-92b7-f2eeff0dac2e.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('40', '20150606//ccef7f62-0286-4713-93d5-11b80fde74d1.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('41', '20150606//8dc28ce5-8f58-4fef-93db-6014117517bd.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('42', '20150606//1cf95c15-28a1-4dc4-a03f-a875212820b4.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('43', '20150606//c5c9bebc-bc55-49f6-b83e-0cb04ab45b35.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('44', '20150614//1b0fc1d9-0a84-41b0-ae66-7b390a12d5e2.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('45', '20150614//6b8db347-ba6d-4013-82a6-59e7a775749a.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('46', '20150615//34cb3250-c381-4b2a-bdcd-040e2cc2c2de.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('47', '20150615//9a861028-2a52-443f-bd1d-7c06206eec70.png', 'avatar');
INSERT INTO `t_user_img` VALUES ('48', '20150615//3c53c1d1-fce7-44ce-a2af-31491cb319d6.jpg', 'image1');
INSERT INTO `t_user_img` VALUES ('49', '20150615//9a4d1ea6-9bf6-4d5c-90c9-c619d35aefe1.jpg', 'image1');

-- ----------------------------
-- Table structure for `t_user_post`
-- ----------------------------
DROP TABLE IF EXISTS `t_user_post`;
CREATE TABLE `t_user_post` (
  `post_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL DEFAULT '0',
  `title` varchar(1024) NOT NULL DEFAULT '',
  `content` varchar(8192) NOT NULL DEFAULT '',
  `img_list` varchar(1024) NOT NULL DEFAULT '' COMMENT '[imgId,imgId,imgId,...]',
  `img_status` varchar(256) NOT NULL DEFAULT '' COMMENT '发贴过程中，帖子的图片的上传情况',
  `nlike` int(11) NOT NULL DEFAULT '0',
  `ndislike` int(11) NOT NULL DEFAULT '0',
  `ncomment` int(11) NOT NULL DEFAULT '0',
  `post_dt` datetime NOT NULL DEFAULT '2015-01-01 00:00:00',
  PRIMARY KEY (`post_id`),
  KEY `user_id_idx` (`user_id`,`post_id`)
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_user_post
-- ----------------------------
INSERT INTO `t_user_post` VALUES ('1', '1', 'A first nice post', 'Hi boy, here is the first post.', '', '{\"0\":0,\"1\":0}\n', '0', '0', '0', '2015-04-16 20:51:19');
INSERT INTO `t_user_post` VALUES ('2', '1', '用手机发的', '好看不', '', '{\"0\":0,\"1\":0}\n', '0', '0', '0', '2015-04-16 20:58:28');
INSERT INTO `t_user_post` VALUES ('3', '3', '立春', '', '', '{\"0\":0}\n', '0', '0', '0', '2015-04-17 10:44:13');
INSERT INTO `t_user_post` VALUES ('4', '4', 'test', 'test', '[8]\n', '', '0', '0', '0', '2015-04-18 12:10:54');
INSERT INTO `t_user_post` VALUES ('5', '4', 'test', '小荷才露', '[9]\n', '', '0', '0', '0', '2015-04-18 16:07:54');
INSERT INTO `t_user_post` VALUES ('6', '4', 'test', '哒哒哒', '[11]\n', '', '0', '0', '0', '2015-04-19 10:11:18');
INSERT INTO `t_user_post` VALUES ('7', '4', 'test', '等你等你', '[12]\n', '', '0', '0', '0', '2015-04-19 10:24:42');
INSERT INTO `t_user_post` VALUES ('8', '4', 'test', '看看', '[13]\n', '', '0', '0', '0', '2015-04-19 10:37:42');
INSERT INTO `t_user_post` VALUES ('9', '4', 'test', '航空港近', '[14]\n', '', '0', '0', '0', '2015-04-19 10:48:38');
INSERT INTO `t_user_post` VALUES ('10', '4', 'test', '哈哈哈哈', '[15]\n', '', '0', '0', '0', '2015-04-19 10:51:38');
INSERT INTO `t_user_post` VALUES ('11', '4', 'test', '嘎嘎嘎', '[16]\n', '', '0', '0', '0', '2015-04-19 11:46:26');
INSERT INTO `t_user_post` VALUES ('12', '4', 'test', '饭饭', '[17]\n', '', '0', '0', '0', '2015-04-19 11:58:48');
INSERT INTO `t_user_post` VALUES ('13', '4', 'test', 'test', '[19]\n', '', '0', '0', '0', '2015-04-21 22:14:06');
INSERT INTO `t_user_post` VALUES ('14', '5', 'test', '户外测试', '[21]\n', '', '0', '0', '0', '2015-05-16 16:58:05');
INSERT INTO `t_user_post` VALUES ('15', '6', 'test', '测试1', '[22]\n', '', '0', '0', '0', '2015-05-16 23:26:03');
INSERT INTO `t_user_post` VALUES ('16', '6', 'test', '继续测试\n', 'null\n', '', '0', '0', '0', '2015-05-17 23:24:18');
INSERT INTO `t_user_post` VALUES ('17', '1', 'Foto testo', 'Mi casa, su casa. Hola, me llamo Hamish. Y tu?', '', '{\"0\":0}\n', '0', '0', '0', '2015-05-25 16:06:39');
INSERT INTO `t_user_post` VALUES ('18', '1', 'Phone uploading test', 'There is a smoke, there is a drugster.', '', '{\"0\":0,\"1\":0}\n', '0', '0', '0', '2015-05-25 16:15:37');
INSERT INTO `t_user_post` VALUES ('19', '7', 'test', '', '[27]\n', '', '0', '0', '0', '2015-06-02 23:16:50');
INSERT INTO `t_user_post` VALUES ('20', '7', 'test', '多么美\n', '[28]\n', '', '0', '0', '0', '2015-06-02 23:17:27');
INSERT INTO `t_user_post` VALUES ('21', '7', 'test', '相当美\n', '[29]\n', '', '0', '0', '0', '2015-06-02 23:18:26');
INSERT INTO `t_user_post` VALUES ('22', '4', 'test', '没有美景图啊\n', '[30]\n', '', '0', '0', '0', '2015-06-06 10:44:04');
INSERT INTO `t_user_post` VALUES ('23', '4', 'test', '', '[34]\n', '', '0', '0', '0', '2015-06-06 11:43:46');
INSERT INTO `t_user_post` VALUES ('24', '4', 'test', '', '[35]\n', '', '0', '0', '0', '2015-06-06 11:45:19');
INSERT INTO `t_user_post` VALUES ('25', '4', 'test', '', '[36]\n', '', '0', '0', '0', '2015-06-06 11:45:50');
INSERT INTO `t_user_post` VALUES ('26', '8', 'test', '禅\n', '[37]\n', '', '0', '0', '0', '2015-06-06 15:25:34');
INSERT INTO `t_user_post` VALUES ('27', '8', 'test', '(～o～)zZ', '[38]\n', '', '0', '1', '0', '2015-06-06 15:27:59');
INSERT INTO `t_user_post` VALUES ('28', '8', 'test', '', '[39]\n', '', '0', '0', '0', '2015-06-06 15:28:20');
INSERT INTO `t_user_post` VALUES ('29', '8', 'test', '', '[40]\n', '', '1', '0', '0', '2015-06-06 15:28:45');
INSERT INTO `t_user_post` VALUES ('30', '8', 'test', '', '[41]\n', '', '3', '0', '0', '2015-06-06 15:28:59');
INSERT INTO `t_user_post` VALUES ('31', '1', 'test', 'Hoyle.', 'null\n', '', '0', '0', '0', '2015-06-06 17:16:54');
INSERT INTO `t_user_post` VALUES ('32', '9', 'test', '小孩玩具', '[48]\n', '', '3', '1', '0', '2015-06-15 00:10:02');
INSERT INTO `t_user_post` VALUES ('33', '9', 'test', '那面板载', '[49]\n', '', '5', '4', '0', '2015-06-15 00:10:42');
