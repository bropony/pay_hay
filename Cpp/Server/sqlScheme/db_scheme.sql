SET FOREIGN_KEY_CHECKS=0;

CREATE TABLE `t_user` (
`user_id`  int(11) NOT NULL AUTO_INCREMENT COMMENT 'userId' ,
`account`  varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`nickname`  varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`login_key`  varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`avatar`  int(11) NOT NULL DEFAULT 0 COMMENT 'avatar img id' ,
`create_dt`  datetime NOT NULL DEFAULT '2015-01-01 00:00:00' ,
PRIMARY KEY (`user_id`),
INDEX `idx_account` (`account`) USING BTREE 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
ROW_FORMAT=Compact
;

CREATE TABLE `t_user_comment` (
`comment_id`  int(11) NOT NULL AUTO_INCREMENT ,
`post_id`  int(11) NOT NULL DEFAULT 0 ,
`from_user_id`  int(11) NOT NULL DEFAULT 0 ,
`from_nickname`  int(11) NOT NULL ,
`content`  varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`comment_dt`  datetime NOT NULL DEFAULT '2015-01-01 00:00:00' ,
PRIMARY KEY (`comment_id`),
INDEX `idx_post_id` (`post_id`) USING BTREE 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
ROW_FORMAT=Compact
;

CREATE TABLE `t_user_img` (
`img_id`  int(11) NOT NULL AUTO_INCREMENT ,
`img_path`  varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`short_desc`  varchar(512) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
PRIMARY KEY (`img_id`),
INDEX `idx_img_id` (`img_id`) USING BTREE 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
ROW_FORMAT=Compact
;

CREATE TABLE `t_user_post` (
`post_id`  int(11) NOT NULL AUTO_INCREMENT ,
`user_id`  int(11) NOT NULL DEFAULT 0 ,
`title`  varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`content`  varchar(8192) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`img_list`  varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '[imgId,imgId,imgId,...]' ,
`nlike`  int(11) NOT NULL DEFAULT 0 ,
`ndislike`  int(11) NOT NULL DEFAULT 0 ,
`ncomment`  int(11) NOT NULL DEFAULT 0 ,
`post_dt`  datetime NOT NULL DEFAULT '2015-01-01 00:00:00' ,
PRIMARY KEY (`post_id`),
INDEX `user_id_idx` (`user_id`, `post_id`) USING BTREE 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
ROW_FORMAT=Compact
;

SET FOREIGN_KEY_CHECKS=1;
