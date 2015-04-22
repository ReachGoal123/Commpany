//
//  main.m
//  Commpany
//
//  Created by wanglin on 14-12-16.
//  Copyright (c) 2014年 tarena. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Subject.h"
int main(int argc, const char * argv[])
{
/*
  
 IOS 笔记
 
 注册Cell
 [self.tableView registerNib:[UINib nibWithNibName:@"TRTableViewCell" bundle:nil] forCellReuseIdentifier:@"Cell"];
 
 self.navigationItem.rightBarButtonItem = self.editButtonItem;
 
 
 
 //编辑模式 编辑的是导航控制器  导航条上得按钮
 
 self.navigationItem.rightBarButtonItem = self.editButtonItem;
 
 
 
 
 
 #pragma mark - 设置UITableView的编辑模式
 -(void)setEditing:(BOOL)editing animated:(BOOL)animated
 {
 //先让父类的方法起作用
 [super setEditing:editing animated:animated];
 //设置子类中的方法 开启了编辑模式
 [self.tableView setEditing:editing animated:animated];
 }
 
 //删除Cell    增加Cell    Cell移动
 //deleteRowsAtIndexPaths  删除
 //insertRowsAtIndexPaths  增加  都有共同的特点
 //先更新数据源    在插入数据或删除数据
 -(void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
 {
 //删除男员工 红色的删除按钮的样式
 if(editingStyle == UITableViewCellEditingStyleDelete)
 {
 //如果是删除样式  就从 manArray中删除数据--->
 //allPerson中去删除数据
 [[self.allPerson objectAtIndex:indexPath.section] removeObjectAtIndex:indexPath.row];
 //第二步 设置删除的动画(如果)
 [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationMiddle];
 }
 //添加女员工
 else
 {
 NSLog(@"添加女员工");
 //先更新数据源 ---->添加
 TRPerson *newPerson = [[TRPerson alloc] init];
 newPerson.no = 140801;
 newPerson.name = @"新入职员工";
 [[self.allPerson objectAtIndex:indexPath.section] insertObject:newPerson atIndex:indexPath.row];
 //设置添加的动画效果（IOS7 动画）
 [tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationRight];
 }
 }
 
 //设置每一个Cell 添加删除 或  添加的标记
 -(UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
 {
 //如果是第一个分段  男员工的时候 删除   女 增加
 if(0 == indexPath.section)
 return UITableViewCellEditingStyleDelete;
 else
 return UITableViewCellEditingStyleInsert;
 }
 
 
 
 
 
 
 
 
 
 
 
 
 //移动
 -(void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath
 {
 
 //拿到要移动的对象
 TRPerson *person=[[self.allPerson objectAtIndex:sourceIndexPath.section]objectAtIndex:sourceIndexPath.row];
 //先删除要移动的对象的原始位置+更新数据
 [[self.allPerson objectAtIndex:sourceIndexPath.section]removeObjectAtIndex:sourceIndexPath.row];
 
 
 //添加到移动对象的目标位置
 
 [[self.allPerson objectAtIndex:destinationIndexPath.section]insertObject:person atIndex:destinationIndexPath.row];
 [self.tableView reloadData];
 
 
 }
 
 
 
 
 
 
 
 //隐藏水平轴
 
 self.tableView.showsVerticalScrollIndicator=NO;
 
 
 
 
 
 
 
 //隐藏状态条
 -(BOOL)prefersStatusBarHidden
 {
 return YES;
 }
 //删除tableview多余的线
 self.tableView.tableFooterView=[[UIView alloc]initWithFrame:CGRectZero];
 
 
 
 FD  NSString
 
 1.在C语言中，是没有专门的字符串类型，我们是通过字符数组来实现一个字符串。
 
 2.在OC中专门的类型来描述字符串类型，NSString。
 
 3.字符串比较特殊，遵循一个"不变模式"，一个字符串一但创建，字符串对象就不可以改变，不可改变的字符串是可以重复使用的，所以相同值的字符串对象，一般只会创建一个对象。
 
 4.有些字符串存在常量值中(代码区)，有些字符串直接存在堆区。
 
 5.字符串的使用
 
 a.字符串创建
 
 1)空字符串 NSString* str = [[NSString alloc]init];
 
 2)字符串在创建的时候，如果已经存在，不会创建新的字符串。NSString* str = @"Hello";
 
 NSString* str2 = @"Hello";
 
 3)按指定格式来创建字符串
 
 NSString* str3 = [NSString stringWithFormat:@"%@ World",str];
 
 4)如果使用stringWithFormat方法创建的字符串，就算内容相同，地址也不一样。
 
 5)通过文件内容创建字符串，注意存在编码集的问题，默认为ASC(不包含中文)，要指定相应的中文编码集(GBK简体中文、GB2312简体中文、BIG5繁体中文、UTF8全世界主流语言…)
 
 参数1 文件的路径
 
 参数2 指定文件的编码集
 
 参数3 出现异常处理
 
 NSString* str7 = [NSString stringWithContentsOfFile:@"/Users/apple/Desktop/testString" encoding:NSUTF8StringEncoding error:nil]
 
 b.字符串的比较 判断等值
 
 1)str==str1 XXX
 
 ==只能判断两个字符串是否指向了同一个对象，(引用的地址是否相同)不能判断两个字符串的内容是否相同。
 
 2)判断两个字符串值是否相同，isEqualToString方法，比较当前字符串与对应字符串值是否相同，严格区分大小写的。
 
 c.比较字符串的大小
 
 通常在字符串排序的时候，需要用到比较字符串的小。
 
 1）compare方法可以比较两个字符串，比较字符串中的字符的ASC码的值
 
 2）返回值有三种结果 NSComparetionResult
 
 NSOrderedSame 两者相等 0
 
 
 
 
 
 
 
 NSOrderedAscending后者比前者大 -1升序
 
 NSOrderedDecending前者比后者大 1降序
 
 d.忽略大小写比较字符串
 
 1)caseInsensitiveCompare这个方法
 
 2)在验证码功能的时候，会用到此方法
 
 六、NSMutableString 可变字符串可以改变字符串内容的功能，它是NSString的子类。
 
 1.初始化
 
 a.空字符串 有意义
 
 NSMutableString* str = [[NSMutableString alloc]init];
 
 b.创建字面值 无意义
 
 不建议用此方式创建可变字符串，字面值字符串的内容，在代码区是无法改变的
 
 NSMutableString* str2 = @"abc";
 
 2.修改字符串的内容
 
 a.在指定位置 添加新的字符串
 
 参数1 添加的字符串内容
 
 参数2 添加的字符串在原字符串中的位置
 
 注：下标是从0开始计算
 
 [str3 insertString:@"123" atIndex:1];
 
 b.可以替换指定位置的字符串
 
 NSRange range={1,3};//位置,长度
 
 [str3 replaceCharactersInRange:range withString:@"bcd"];
 
 c.删除指定位置的字符串，后面的字符串会向前补齐
 
 [str3 deleteCharactersInRange:range];
 
 3.两个字符串对象的操作
 
 a.追加字符串
 
 [str4 appendString:@"bcd"];
 
 b.按照指定格式追加字符串 str4 = abcbcd
 
 [str4 appendFormat:@"123%@bcd",@"def”];
 
 
 
 4.截取字符串
 
 a.从指定下标开始，包含开始位置截取字符串
 
 subStringFromIndex
 
 从中间到最后
 
 b.从0开始，到指定位置，不包含指定位置
 
 subStringToIndex
 
 从开始到中间
 
 c.指定范围截取字符串
 
 subStringWithRange
 
 NSRange range = {location,length};
 
 5.字符串大小写转换
 
 a.将所有的字符串内容变为大写字母
 
 uppercaseString
 
 b.将所有的字符串内容变为小写字母
 
 lowercaseString
 
 c.将单词的首字母大写
 
 capitalizedString
 
 转换
 
 6.得到字符串的前缀和后缀
 
 TRStudent.h 前缀(TR)和后缀(.h)
 
 如果一个字符串是文件名，那么可以得到这个字符串的前缀和后缀。
 
 a.判断一个文件是否有某个前缀
 
 BOOL b = [str hasPrefix:@"TR"];
 
 b.判断一个文件是否有某个后缀
 
 BOOL b = [str hasSuffix:@".h"];
 
 
 
 练习：
 
 根据身份证号码，求出生年月日？
 
 230119197007010000
 
 1970年07月01日
 
 
 
 一、NSNumber数值对象
 
 在很多类使用的时候，如果使用数值，就需要将数值转换成对象类型，而基本数据类型是无法使用的，所以说我们就要封装基本数据类型变为对象类型，数值对象的常用处理方式和使用与基本数据类型无差别。
 
 1.数字对象的初始化
 
 //封装
 
 int i = 10;//基本数据类型
 
 //对象类型
 
 NSNumber* number = [NSNumber numberWithInt:i];
 
 2.数字对象转换为基本数据类型
 
 //解封
 
 int i2 =[number intValue];
 
 二、NSValue
 
 1.有时需要创建一个对象，以密切反应原始数据类型或者数据结构，这种情况就需要使用NSValue类，它可以将任何C中有效的变量类型封装成对象类型。
 
 2.NSNumber是NSValue的子类
 
 3.使用NSValue封装一个结构体
 
 a.定义一个结构体类型
 
 typedef struct _Point{
 
 int x;
 
 int y;
 
 }Point2;
 
 b.声明一个结构变量并且赋值
 
 Point2 point;
 
 point.x = 10;
 
 point.y = 20;
 
 c.通过NSValue类，将结构类型封装成NSValue对象
 
 参数1 结构体变量的内存地址
 
 参数2 内存地址对应的结构体类型
 
 NSValue* value = [NSValue valueWithBytes:&point objCType:@encode(Point2)];
 
 d.把结构体对象转换成结构体类型
 
 Point2 point2;
 
 [value getValue:&point2];
 
 
 
 三、NSDate 日期
 
 1.NSDate存储的是时间信息，默认存储的是世界标准时间(UTC)，输出时需要根据时区转换为本地时间。中国大陆、香港、澳门、台湾…的时间增均与UTC时间差为+8，也就是UTC+8。
 
 2.初始化 得到当前的时间
 
 NSDate* date = [[NSDate alloc]init];
 
 3.得到一个时间，和当前比延迟30秒
 
 NSDate* date2 = [NSDate dateWithTimeIntervalSinceNow:30];
 
 4.和时间对比 返回秒数
 
 NSTimeInterval second = [date timeIntervalSince1970];
 
 5.比较两个时间 哪个更早
 
 NSDate* earlierDate = [date earlierDate:date2];
 
 6.比较两个时间 哪个更晚
 
 NSDate* laterDate = [date laterDate:date2];
 
 7.将世界标准时间转换成当地时间
 
 
 
 8.将UTC时间转换为当地时间
 
 a.创建模板对象
 
 NSDateFormatter* dateFormatter
 
 =[[NSDateFormatter alloc]init];
 
 //hh12小时制mm分钟ss秒 HH24小时制
 
 //MM月dd日yyyy年
 
 dateFormatter.dateFormat = @"yyyy-MM-dd hh:mm:ss";
 
 b.通过模板对象 将时间对象转换成字符串
 
 NSString* strDate = [dateFormatter stringFromDate:date];
 
 四、NSArray 数组1.概述
 
 数组是一组有序的集合，通过索引下标取到数组中的各个元素，与字符串相同，数组也有可变数组(NSMutableArray)和不可变数组(NSArray)，数组中不可以保存基本数据类型、结构体数据类型，需要使用NSNumber和NSValue进行数据"封装"。
 
 2.初始化方法
 
 a.空数组
 
 NSArray* array = [NSArray array];
 
 b.数组中只有一个元素
 
 NSArray* array2 = [NSArray arrayWithObject:@"one"];
 
 c.数组中有多个元素
 
 NSArray* array3 = [NSArray arrayWithObjects:@"one",@"two",@"three", nil];
 
 2.初始化方法
 
 d.通过一个已有的数组 创建新的数组
 
 NSArray* array4 = [NSArray arrayWithArray:array3];
 
 3.数组的常用方法
 
 a.数组的长度
 
 NSUInteger length = [array4 count];
 
 b.通过数组的下标得到数组中元素
 
 NSString* objStr = [array4 objectAtIndex:0];
 
 3.数组的常用方法
 
 c.遍历数组
 
 for (int i = 0; i<[array4 count]; i++) {
 
 NSString* str = [array4 objectAtIndex:i];
 
 }
 
 
 
 1.向数组中存放数据，
 
 int i = 10;char c = 'a';
 
 BOOL b = YES
 
 TRStudent age:18 name:zhangsan;
 
 当前的系统时间
 
 2.遍历输出数组对象。
 
 
 1.创建一个学生类TRStudent，有年龄、有姓名，创建五个学生对象，放到数组中，遍历数组，输出学生的姓名和年龄。
 
 2.查询（遍历）五个学生信息，只显示姓名为zhangsan的信息。
 
 3.只显示年龄为18岁学生的信息。
 
 
 
 
 
 
 
 
 
 
 
   */
}

