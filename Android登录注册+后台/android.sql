/*
 Navicat Premium Data Transfer

 Source Server         : Android
 Source Server Type    : MySQL
 Source Server Version : 80011
 Source Host           : localhost:3306
 Source Schema         : android

 Target Server Type    : MySQL
 Target Server Version : 80011
 File Encoding         : 65001

 Date: 28/06/2019 14:43:58
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for address
-- ----------------------------
DROP TABLE IF EXISTS `address`;
CREATE TABLE `address`  (
  `address` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `username` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `tel` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of address
-- ----------------------------
INSERT INTO `address` VALUES ('SC', '333', '791');

-- ----------------------------
-- Table structure for cart
-- ----------------------------
DROP TABLE IF EXISTS `cart`;
CREATE TABLE `cart`  (
  `username` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `cid` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `num` int(11) NULL DEFAULT NULL,
  `src` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of cart
-- ----------------------------
INSERT INTO `cart` VALUES ('1', 'IPhoneX', 5, '/Pictures/Commodity/IPhoneX.jpg');
INSERT INTO `cart` VALUES ('1', 'Mate20', 2, '/Pictures/Commodity/Mate20.jpg');
INSERT INTO `cart` VALUES ('12', 'WenZhang', 5, '/Pictures/Commodity/WenZhang.jpg');
INSERT INTO `cart` VALUES ('333', '22', 1, '1');

-- ----------------------------
-- Table structure for commodity
-- ----------------------------
DROP TABLE IF EXISTS `commodity`;
CREATE TABLE `commodity`  (
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cid` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `category` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `price` int(10) NULL DEFAULT NULL,
  `num` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`cid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of commodity
-- ----------------------------
INSERT INTO `commodity` VALUES ('IPhoneX', 'IPhoneX', '手机', 9000, 100);
INSERT INTO `commodity` VALUES ('Mate20', 'Mate20', '手机', 5000, 100);
INSERT INTO `commodity` VALUES ('蚊帐', 'WenZhang', '家居', 29, 1000);

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `username` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tel` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `type` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `sex` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`username`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('1', '55551111', '11111111111111', 'USER', 'male');
INSERT INTO `user` VALUES ('12', '1', '222222', 'USER', 'male');
INSERT INTO `user` VALUES ('123', '55551111', '111111', 'USER', 'male');
INSERT INTO `user` VALUES ('1231', '55551111112', '11111111111111', 'USER', 'male');
INSERT INTO `user` VALUES ('admin', '1', '111111', 'ADMIN', 'male');
INSERT INTO `user` VALUES ('xzz', '123', '55551111', 'USER', 'xxxxxxxxxxxxxxxxxxxx`');
INSERT INTO `user` VALUES ('xzzz', '135', '111111', 'USER', 'male');

SET FOREIGN_KEY_CHECKS = 1;
