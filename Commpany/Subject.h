//
//  Subject.h
//  Commpany
//
//  Created by wanglin on 14-12-16.
//  Copyright (c) 2014年 tarena. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Subject : NSObject
/*
 iOS进阶面试题----经典10道
 
 随着iOS平台开发的职位的增加，笔试、面试也越来越有“套路”，这里我总结了一些面试题，多数是Objective-C的基础知识，适合于面试新人，答案是我自己答的，不准确的地方，欢迎指出。
 
 1.   Object－c的类可以多重继承么？可以实现多个接口么？Category是什么？重写一个类的方式用继承好还是分类好？为什么？
 
 Object-c的类不可以多重继承；可以实现多个接口，通过实现多个接口可以完成C++的多重继承；Category是类别，一般情况用分类好，用Category去重写类的方法，仅对本Category有效，不会影响到其他类与原有类的关系。
 
 
 
 2.#import 跟#include 又什么区别，@class呢, ＃import<> 跟 #import”"又什么区别？
 
 #import是Objective-C导入头文件的关键字，#include是C/C++导入头文件的关键字,使用#import头文件会自动只导入一次，不会重复导入，相当于#include和#pragma once；@class告诉编译器某个类的声明，当执行时，才去查看类的实现文件，可以解决头文件的相互包含；#import<>用来包含系统的头文件，#import””用来包含用户头文件。
 
 
 
 3. 属性readwrite，readonly，assign，retain，copy，nonatomic 各是什么作用，在那种情况下用？
 
 readwrite 是可读可写特性；需要生成getter方法和setter方法时
 
 readonly 是只读特性  只会生成getter方法 不会生成setter方法 ;不希望属性在类外改变
 
 assign 是赋值特性，setter方法将传入参数赋值给实例变量；仅设置变量时；
 
 retain 表示持有特性，setter方法将传入参数先保留，再赋值，传入参数的retaincount会+1;
 
 copy 表示赋值特性，setter方法将传入对象复制一份；需要完全一份新的变量时。
 
 nonatomic 非原子操作，决定编译器生成的setter getter是否是原子操作，atomic表示多线程安全，一般使用nonatomic
 
 
 
 4.写一个setter方法用于完成@property （nonatomic,retain）NSString *name,写一个setter方法用于完成@property（nonatomic，copy）NSString *name
 
 [cpp] view plaincopyprint?
 
 - (void) setName:(NSString*) str
 {
 [str retain];
 [name release];
 name = str;
 }
 - (void)setName:(NSString *)str
 {
 id t = [str copy];
 [name release];
 name = t;
 }
 
 
 5.对于语句NSString*obj = [[NSData alloc] init]; obj在编译时和运行时分别时什么类型的对象？
 
 编译时是NSString的类型；运行时是NSData类型的对象
 
 
 
 6.常见的object-c的数据类型有那些， 和C的基本数据类型有什么区别？如：NSInteger和int
 
 object-c的数据类型有NSString，NSNumber，NSArray，NSMutableArray，NSData等等，这些都是class，创建后便是对象，而C语言的基本数据类型int，只是一定字节的内存空间，用于存放数值；NSInteger是基本数据类型，并不是NSNumber的子类，当然也不是NSObject的子类。NSInteger是基本数据类型Int或者Long的别名（NSInteger的定义typedef long NSInteger），它的区别在于，NSInteger会根据系统是32位还是64位来决定是本身是int还是Long。
 
 7.id 声明的对象有什么特性？
 
 Id 声明的对象具有运行时的特性，即可以指向任意类型的objcetive-c的对象；
 
 
 
 8.Objective-C如何对内存管理的,说说你的看法和解决方法?
 
 Objective-C的内存管理主要有三种方式ARC（自动内存计数）、手动内存计数、内存池。
 
 
 
 9.内存管理的几条原则时什么？按照默认法则.那些关键字生成的对象
 
 需要手动释放？在和property结合的时候怎样有效的避免内存泄露？
 
 谁申请，谁释放
 
 遵循Cocoa Touch的使用原则；
 
 内存管理主要要避免“过早释放”和“内存泄漏”，对于“过早释放”需要注意@property设置特性时，一定要用对特性关键字，对于“内存泄漏”，一定要申请了要负责释放，要细心。
 
 关键字alloc 或new 生成的对象需要手动释放；
 
 设置正确的property属性，对于retain需要在合适的地方释放，
 
 
 
 10.如何对iOS设备进行性能测试?
 
 Profile-> Instruments ->Time Profiler
 
 11.看下面的程序,第一个NSLog会输出什么？这时str的retainCount是多少？第二个和第三个呢？ 为什么？
 
 [cpp] view plaincopyprint?
 
 =======================================================
 NSMutableArray* ary = [[NSMutableArray array] retain];
 NSString *str = [NSString stringWithFormat:@"test"];
 [strretain];
 [aryaddObject:str];
 NSLog(@"%@%d",str,[str retainCount]);
 [strretain];
 [strrelease];
 [strrelease];
 NSLog(@"%@%d",str,[str retainCount]);
 [aryremoveAllObjects];
 NSLog(@"%@%d",str,[str retainCount]);
 =======================================================
 str的retainCount创建+1，retain+1，加入数组自动+1
 
 3
 
 retain+1，release-1，release-1
 
 2
 
 数组删除所有对象，所有数组内的对象自动-1
 
 1
 
 12. Object C中创建线程的方法是什么？如果在主线程中执行代码，方法是什么？如果想延时执行代码、方法又是什么？
 
 线程创建有三种方法：使用NSThread创建、使用GCD的dispatch、使用子类化的NSOperation,然后将其加入NSOperationQueue;在主线程执行代码，方法是performSelectorOnMainThread，如果想延时执行代码可以用performSelector:onThread:withObject:waitUntilDone:
 
 13.描述一下iOS SDK中如何实现MVC的开发模式
 
 MVC是模型、试图、控制开发模式，对于iOS SDK，所有的View都是视图层的，它应该独立于模型层，由视图控制层来控制。所有的用户数据都是模型层，它应该独立于视图。所有的ViewController都是控制层，由它负责控制视图，访问模型数据。
 
 
 
 iOS进阶面试题----Block部分
 
 iOS进阶面试题----多线程部分
 
 1.Difference between shallow copy and deep copy?
 浅复制和深复制的区别？
 答案：浅层复制：只复制指向对象的指针，而不复制引用对象本身。
 深层复制：复制引用对象本身。
 意思就是说我有个A对象，复制一份后得到A_copy对象后，对于浅复制来说，A和A_copy指向的是同一个内存资源，复制的只不过是是一个指针，对象本身资源
 还是只有一份，那如果我们对A_copy执行了修改操作,那么发现A引用的对象同样被修改，这其实违背了我们复制拷贝的一个思想。深复制就好理解了,内存中存在了
 两份独立对象本身。
 用网上一哥们通俗的话将就是：
 浅复制好比你和你的影子，你完蛋，你的影子也完蛋
 深复制好比你和你的克隆人，你完蛋，你的克隆人还活着。
 
 2.What is advantage of categories? What is difference between implementing a category and inheritance?
 类别的作用？继承和类别在实现中有何区别？
 答案：category 可以在不获悉，不改变原来代码的情况下往里面添加新的方法，只能添加，不能删除修改。
 并且如果类别和原来类中的方法产生名称冲突，则类别将覆盖原来的方法，因为类别具有更高的优先级。
 类别主要有3个作用：
 (1)将类的实现分散到多个不同文件或多个不同框架中。
 (2)创建对私有方法的前向引用。
 (3)向对象添加非正式协议。
 继承可以增加，修改或者删除方法，并且可以增加属性。
 
 3.Difference between categories and extensions?
 类别和类扩展的区别。
 答案：category和extensions的不同在于 后者可以添加属性。另外后者添加的方法是必须要实现的。
 extensions可以认为是一个私有的Category。
 
 4.Difference between protocol in objective c and interfaces in java?
 oc中的协议和java中的接口概念有何不同？
 答案：OC中的代理有2层含义，官方定义为 formal和informal protocol。前者和Java接口一样。
 informal protocol中的方法属于设计模式考虑范畴，不是必须实现的，但是如果有实现，就会改变类的属性。
 其实关于正式协议，类别和非正式协议我很早前学习的时候大致看过，也写在了学习教程里
 “非正式协议概念其实就是类别的另一种表达方式“这里有一些你可能希望实现的方法，你可以使用他们更好的完成工作”。
 这个意思是，这些是可选的。比如我门要一个更好的方法，我们就会申明一个这样的类别去实现。然后你在后期可以直接使用这些更好的方法。
 这么看，总觉得类别这玩意儿有点像协议的可选协议。"
 现在来看，其实protocal已经开始对两者都统一和规范起来操作，因为资料中说“非正式协议使用interface修饰“，
 现在我们看到协议中两个修饰词：“必须实现(@requied)”和“可选实现(@optional)”。
 
 5.What are KVO and KVC?
 答案：kvc:键 - 值编码是一种间接访问对象的属性使用字符串来标识属性，而不是通过调用存取方法，直接或通过实例变量访问的机制。
 很多情况下可以简化程序代码。apple文档其实给了一个很好的例子。
 kvo:键值观察机制，他提供了观察某一属性变化的方法，极大的简化了代码。
 具体用看到嗯哼用到过的一个地方是对于按钮点击变化状态的的监控。
 比如我自定义的一个button
 [cpp]
 [self addObserver:self forKeyPath:@"highlighted" options:0 context:nil];
 
 
 #pragma mark KVO
 
 - (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
 {
 if ([keyPath isEqualToString:@"highlighted"] ) {
 [self setNeedsDisplay];
 }
 }
 
 对于系统是根据keypath去取的到相应的值发生改变，理论上来说是和kvc机制的道理是一样的。
 对于kvc机制如何通过key寻找到value：
 “当通过KVC调用对象时，比如：[self valueForKey:@”someKey”]时，程序会自动试图通过几种不同的方式解析这个调用。首先查找对象是否带有 someKey 这个方法，如果没找到，会继续查找对象是否带有someKey这个实例变量（iVar），如果还没有找到，程序会继续试图调用 -(id) valueForUndefinedKey:这个方法。如果这个方法还是没有被实现的话，程序会抛出一个NSUndefinedKeyException异常错误。
 
 (cocoachina.com注：Key-Value Coding查找方法的时候，不仅仅会查找someKey这个方法，还会查找getsomeKey这个方法，前面加一个get，或者_someKey以及_getsomeKey这几种形式。同时，查找实例变量的时候也会不仅仅查找someKey这个变量，也会查找_someKey这个变量是否存在。）
 
 设计valueForUndefinedKey:方法的主要目的是当你使用-(id)valueForKey方法从对象中请求值时，对象能够在错误发生前，有最后的机会响应这个请求。这样做有很多好处，下面的两个例子说明了这样做的好处。“
 来至cocoa，这个说法应该挺有道理。
 因为我们知道button却是存在一个highlighted实例变量.因此为何上面我们只是add一个相关的keypath就行了，
 可以按照kvc查找的逻辑理解，就说的过去了。
 
 6.What is purpose of delegates?
 代理的作用？
 答案：代理的目的是改变或传递控制链。允许一个类在某些特定时刻通知到其他类，而不需要获取到那些类的指针。可以减少框架复杂度。
 另外一点，代理可以理解为java中的回调监听机制的一种类似。
 
 7.What are mutable and immutable types in Objective C?
 oc中可修改和不可以修改类型。
 答案：可修改不可修改的集合类。这个我个人简单理解就是可动态添加修改和不可动态添加修改一样。
 比如NSArray和NSMutableArray。前者在初始化后的内存控件就是固定不可变的，后者可以添加等，可以动态申请新的内存空间。
 
 8.When we call objective c is runtime language what does it mean?
 我们说的oc是动态运行时语言是什么意思？
 答案：多态。 主要是将数据类型的确定由编译时，推迟到了运行时。
 这个问题其实浅涉及到两个概念，运行时和多态。
 简单来说，运行时机制使我们直到运行时才去决定一个对象的类别，以及调用该类别对象指定方法。
 多态：不同对象以自己的方式响应相同的消息的能力叫做多态。意思就是假设生物类（life）都用有一个相同的方法-eat;
 那人类属于生物，猪也属于生物，都继承了life后，实现各自的eat，但是调用是我们只需调用各自的eat方法。
 也就是不同的对象以自己的方式响应了相同的消息（响应了eat这个选择器）。
 因此也可以说，运行时机制是多态的基础？~~~
 
 9.what is difference between NSNotification and protocol?
 通知和协议的不同之处？
 答案：协议有控制链(has-a)的关系，通知没有。
 首先我一开始也不太明白，什么叫控制链（专业术语了~）。但是简单分析下通知和代理的行为模式，我们大致可以有自己的理解
 简单来说，通知的话，它可以一对多，一条消息可以发送给多个消息接受者。
 代理按我们的理解，到不是直接说不能一对多，比如我们知道的明星经济代理人，很多时候一个经济人负责好几个明星的事务。
 只是对于不同明星间，代理的事物对象都是不一样的，一一对应，不可能说明天要处理A明星要一个发布会，代理人发出处理发布会的消息后，别称B的
 发布会了。但是通知就不一样，他只关心发出通知，而不关心多少接收到感兴趣要处理。
 因此控制链（has-a从英语单词大致可以看出，单一拥有和可控制的对应关系。
 
 10.What is push notification?
 什么是推送消息？
 答案：太简单，不作答~~~~~~~~~~
 这是cocoa上的答案。
 其实到不是说太简单，只是太泛泛的一个概念的东西。就好比说，什么是人。
 推送通知更是一种技术。
 简单点就是客户端获取资源的一种手段。
 普通情况下，都是客户端主动的pull。
 推送则是服务器端主动push。 测试push的实现可以查看该博文。
 
 
 
 11.Polymorphism？
 关于多态性
 答案：多态，子类指针可以赋值给父类。
 这个题目其实可以出到一切面向对象语言中，
 因此关于多态，继承和封装基本最好都有个自我意识的理解，也并非一定要把书上资料上写的能背出来。
 最重要的是转化成自我理解。
 
 12.Singleton?
 对于单例的理解
 答案：11，12题目其实出的有点泛泛的感觉了，可能说是编程语言需要或是必备的基础。
 基本能用熟悉的语言写出一个单例，以及可以运用到的场景或是你编程中碰到过运用的此种模式的框架类等。
 进一步点，考虑下如何在多线程访问单例时的安全性。
 
 13.What is responder chain?
 说说响应链
 答案： 事件响应链。包括点击事件，画面刷新事件等。在视图栈内从上至下，或者从下之上传播。
 可以说点事件的分发，传递以及处理。具体可以去看下touch事件这块。因为问的太抽象化了
 严重怀疑题目出到越后面就越笼统。
 
 可以从责任链模式，来讲通过事件响应链处理，其拥有的扩展性
 
 14.Difference between frame and bounds?
 frame和bounds有什么不同？
 答案:frame指的是：该view在父view坐标系统中的位置和大小。（参照点是父亲的坐标系统）
 bounds指的是：该view在本身坐标系统中 的位置和大小。（参照点是本身坐标系统）
 
 15.Difference between method and selector?
 方法和选择器有何不同？
 答案：selector是一个方法的名字，method是一个组合体，包含了名字和实现.
 详情可以看apple文档。
 
 16.Is there any garbage collection mechanism in Objective C.?
 OC的垃圾回收机制？
 答案： OC2.0有Garbage collection，但是iOS平台不提供。
 一般我们了解的objective-c对于内存管理都是手动操作的，但是也有自动释放池。
 但是差了大部分资料，貌似不要和arc机制搞混就好了。
 求更多~~
 
 17.NSOperation queue?
 答案：存放NSOperation的集合类。
 操作和操作队列，基本可以看成java中的线程和线程池的概念。用于处理ios多线程开发的问题。
 网上部分资料提到一点是，虽然是queue，但是却并不是带有队列的概念，放入的操作并非是按照严格的先进现出。
 这边又有个疑点是，对于队列来说，先进先出的概念是Afunc添加进队列，Bfunc紧跟着也进入队列，Afunc先执行这个是必然的，
 但是Bfunc是等Afunc完全操作完以后，B才开始启动并且执行，因此队列的概念离乱上有点违背了多线程处理这个概念。
 但是转念一想其实可以参考银行的取票和叫号系统。
 因此对于A比B先排队取票但是B率先执行完操作，我们亦然可以感性认为这还是一个队列。
 但是后来看到一票关于这操作队列话题的文章，其中有一句提到
 “因为两个操作提交的时间间隔很近，线程池中的线程，谁先启动是不定的。”
 瞬间觉得这个queue名字有点忽悠人了，还不如pool~
 综合一点，我们知道他可以比较大的用处在于可以帮组多线程编程就好了。
 
 18.What is lazy loading?
 答案：懒汉模式，只在用到的时候才去初始化。
 也可以理解成延时加载。
 我觉得最好也最简单的一个列子就是tableView中图片的加载显示了。
 一个延时载，避免内存过高，一个异步加载，避免线程堵塞。
 
 19.Can we use two tableview controllers on one viewcontroller?
 是否在一个视图控制器中嵌入两个tableview控制器？
 答案：一个视图控制只提供了一个View视图，理论上一个tableViewController也不能放吧，
 只能说可以嵌入一个tableview视图。当然，题目本身也有歧义，如果不是我们定性思维认为的UIViewController，
 而是宏观的表示视图控制者，那我们倒是可以把其看成一个视图控制者，它可以控制多个视图控制器，比如TabbarController
 那样的感觉。
 
 20.Can we use one tableview with two different datasources? How you will achieve this?
 一个tableView是否可以关联两个不同的数据源？你会怎么处理？
 答案：首先我们从代码来看，数据源如何关联上的，其实是在数据源关联的代理方法里实现的。
 因此我们并不关心如何去关联他，他怎么关联上，方法只是让我返回根据自己的需要去设置如相关的数据源。
 因此，我觉得可以设置多个数据源啊，但是有个问题是，你这是想干嘛呢？想让列表如何显示，不同的数据源分区块显示？
 
 
 
 
 
 
 
 iOS进阶面试题----多线程部分
 
 
 
 1.When to use NSMutableArray and when to use NSArray?
 
 什么时候使用NSMutableArray，什么时候使用NSArray？
 
 答案：当数组在程序运行时，需要不断变化的，使用NSMutableArray，当数组在初始化后，便不再改变的，使用NSArray。需要指出的是，使用NSArray只表明的是该数组在运行时不发生改变，即不能往NSAarry的数组里新增和删除元素，但不表明其数组內的元素的内容不能发生改变。NSArray是线程安全的，NSMutableArray不是线程安全的，多线程使用到NSMutableArray需要注意。
 
 2.Give us example of what are delegate methods and what are data source methods of uitableview.
 
 给出委托方法的实例，并且说出UITableVIew的Data Source方法
 
 答案：CocoaTouch框架中用到了大量委托，其中UITableViewDelegate就是委托机制的典型应用，是一个典型的使用委托来实现适配器模式，其中UITableViewDelegate协议是目标，tableview是适配器，实现UITableViewDelegate协议，并将自身设置为talbeview的delegate的对象，是被适配器，一般情况下该对象是UITableViewController。
 
 UITableVIew的Data Source方法有- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;
 
 - (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
 
 
 3.How many autorelease you can create in your application? Is there any limit?
 
 在应用中可以创建多少autorelease对象，是否有限制？
 
 答案：无
 
 4.If we don’t create any autorelease pool in our application then is there any autorelease pool already provided to us?
 
 如果我们不创建内存池，是否有内存池提供给我们？
 
 答案:界面线程维护着自己的内存池，用户自己创建的数据线程，则需要创建该线程的内存池
 
 5.When you will create an autorelease pool in your application?
 
 什么时候需要在程序中创建内存池？
 
 答案：用户自己创建的数据线程，则需要创建该线程的内存池
 
 6.When retain count increase?
 
 什么时候内存计数会增加？
 
 答案：见iOS面试题（一）
 
 7.What are commonly used NSObject class methods?
 
 类NSObject的那些方法经常被使用？
 
 答案：NSObject是Objetive-C的基类，其由NSObject类及一系列协议构成。
 
 其中类方法alloc、class、 description 对象方法init、dealloc、– performSelector:withObject:afterDelay:等经常被使用
 
 8.What is convenience constructor?
 
 什么是简便构造方法？
 
 答案：简便构造方法一般由CocoaTouch框架提供，如NSNumber的 + numberWithBool:  + numberWithChar:  + numberWithDouble:  + numberWithFloat:  + numberWithInt:
 
 Foundation下大部分类均有简便构造方法，我们可以通过简便构造方法，获得系统给我们创建好的对象，并且不需要手动释放。
 
 9.How to design universal application in Xcode?
 
 如何使用Xcode设计通用应用？
 
 答案：使用MVC模式设计应用，其中Model层完成脱离界面，即在Model层，其是可运行在任何设备上，在controller层，根据iPhone与iPad（独有UISplitViewController）的不同特点选择不同的viewController对象。在View层，可根据现实要求，来设计，其中以xib文件设计时，其设置其为universal。
 
 10.What is keyword atomic in Objective C?
 
 在Objetive-C什么时原子关键字
 
 答案：atomic，nonatomic见iOS面试题（一）
 
 11.What are UIView animations?
 
 UIView的动画效果有那些？
 
 答案：有很多，如  UIViewAnimationOptionCurveEaseInOut     UIViewAnimationOptionCurveEaseIn     UIViewAnimationOptionCurveEaseOut    UIViewAnimationOptionTransitionFlipFromLeft   UIViewAnimationOptionTransitionFlipFromRight     UIViewAnimationOptionTransitionCurlUpUIViewAnimationOptionTransitionCurlDown
 
 如何使用可见该博文
 
 12.How can you store data in iPhone applications?
 
 在iPhone应用中如何保存数据？
 
 答案：有以下几种保存机制：
 
 1.通过web服务，保存在服务器上
 
 2.通过NSCoder固化机制，将对象保存在文件中
 
 3.通过SQlite或CoreData保存在文件数据库中
 
 13.What is coredata?
 
 什么是coredata？
 
 答案：coredata是苹果提供一套数据保存框架，其基于SQlite
 
 14.What is NSManagedObject model?
 
 什么是NSManagedObject模型？
 
 答案：NSManagedObject是NSObject的子类 ，也是coredata的重要组成部分，它是一个通用的类,实现了core data 模型层所需的基本功能，用户可通过子类化NSManagedObject，建立自己的数据模型。
 
 15.What is NSManagedobjectContext?
 
 什么是NSManagedobjectContext？
 
 答案：NSManagedobjectContext对象负责应用和数据库之间的交互。
 
 16.What is predicate?
 
 什么是谓词？
 
 答案：谓词是通过NSPredicate，是通过给定的逻辑条件作为约束条件，完成对数据的筛选。
 
 predicate = [NSPredicate predicateWithFormat:@"customerID == %d",n];
 
 a = [customers filteredArrayUsingPredicate:predicate];
 
 
 17.What kind of persistence store we can use with coredata?
 
 和coredata一起有哪几种持久化存储机制？
 
 答案：存入到文件、 存入到NSUserDefaults（系统plist文件中）、存入到Sqlite文件数据库
 
 
 
 
 
 1 谈谈对Block 的理解？并写出一个使用Block执行UIVew动画？
 
 答案：Block是可以获取其他函数局部变量的匿名函数，其不但方便开发，并且可以大幅提高应用的执行效率（多核心CPU可直接处理Block指令）
 
 
 [cpp] view plaincopyprint?
 
 [UIView transitionWithView:self.view
 duration:0.2
 options:UIViewAnimationOptionTransitionFlipFromLeft
 animations:^{ [[blueViewController view] removeFromSuperview]; [[self view] insertSubview:yellowViewController.view atIndex:0]; }
 completion:NULL];
 
 2 写出上面代码的Block的定义。
 
 答案：
 
 typedef void(^animations) (void);
 
 typedef void(^completion) (BOOL finished);
 
 
 
 3 试着使用+ beginAnimations:context:以及上述Block的定义，写出一个可以完成
 
 + (void)transitionWithView:(UIView *)view duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(4_0);操作的函数执行部分
 
 答案：无
 
 网络部分
 
 3 做过的项目是否涉及网络访问功能，使用什么对象完成网络功能？
 
 答案：ASIHTTPRequest(AFN)与NSURLConnection
 
 4 简单介绍下NSURLConnection类及+ sendSynchronousRequest:returningResponse:error:与– initWithRequest:delegate:两个方法的区别？
 
 答案:  NSURLConnection主要用于网络访问，其中+ sendSynchronousRequest:returningResponse:error:是同步访问数据，即当前线程会阻塞，并等待request的返回的response，而– initWithRequest:delegate:使用的是异步加载，当其完成网络访问后，会通过delegate回到主线程，并其委托的对象。
 
 面试
 
 1、堆和栈什么区别？
 
 答：管理方式：对于栈来讲，是由编译器自动管理，无需我们手工控制；对于堆来说，释放工作由程序员控制，容易产生memory leak。
 
 
 2、数组和链表什么区别？
 
 答：数组是将元素在内存中连续存放，由于每个元素占用内存相同，可以通过下标迅速访问数组中任何元素。
 
 链表恰好相反，链表中的元素在内存中不是顺序存储的，而是通过存在元素中的指针联系到一起。
 
 3、delegate和notification什么区别，什么情况使用？
 
 答：Delegate:
 消息的发送者(sender)告知接收者(receiver)某个事件将要发生，delegate同意然然后发送者响应事件，
 
 delegate机制使得接收者可以改变发送者的行为。
 
 通常发送者和接收者的关系是直接的一对多的关系。
 
 Notification:
 消息的发送者告知接收者事件已经发生或者将要发送，仅此而已，接收者并不能反过来影响发送者的行为。
 
 通常发送者和接收者的关系是间接的多对多关系。
 
 
 
 4、什么是MVC，为什么使用MVC，有什么好处？
 
 答： 分别为： 模型(Model),视图(View)和控制Controller)。
 
 模型（Model） “数据模型”（Model）用于封装与应用程序的业务逻辑相关的数据以及对数据的处理方法。
 
 “模型”有对数据直接访问的权力，例如对数据库的访问。
 
 视图（View） 视图层能够实现数据有目的显示。
 
 控制器（Controller） 控制器起到不同层面间的组织作用，用于控制应用程序的流程。
 
 
 5、从一个数组中找出重复的元素打印出来
 
 
 
 NSArray *arr = [NSArrayarrayWithObjects:@"1",@"2",@"1",@"7",@"4",@"5",@"2",@"6",@"5",nil];
 
 NSMutableArray *arrmu = [[NSMutableArrayalloc]init];//过滤
 
 NSMutableArray *sameArray = [[NSMutableArrayalloc]init];//找出相同的
 
 for (int i = 0 ; i < [arrcount]; i++) {
 
 
 
 id str = [arr objectAtIndex:i];
 
 if ([arrmu count] == 0)
 
 {
 
 [arrmuaddObject:str];
 
 }
 
 else{
 
 BOOL flag = NO;
 
 for (int j = 0; j < [arrmucount]; j++ ) {
 
 if ([strisEqual:[arrmu objectAtIndex:j]])
 
 {
 
 [sameArrayaddObject:str];
 
 flag =YES;
 
 break;
 
 }
 
 else{
 
 flag =NO;
 
 }
 
 }
 
 if (flag == NO) {
 
 
 
 [ arrmuaddObject:str];
 
 }
 
 }
 
 }
 
 
 
 NSLog(@"sameArray : %@",sameArray);
 
 还有两种直接找出的方法，上代码：
 
 一：
 
 NSArray *arr = [NSArrayarrayWithObjects:@"1",@"2",@"1",nil];
 
 NSSet *set = [NSSetsetWithArray:arr];
 
 NSLog(@"%@",[setallObjects]);
 
 二：
 
 NSArray *arr =@[@1,@2,@1];
 
 NSMutableDictionary *dict = [NSMutableDictionarydictionary];
 
 for (NSNumber *numberin arr) {
 
 [dictsetObject:numberforKey:number];
 
 }
 
 NSLog(@"%@",[dictallValues]);
 
 
 
 
 
 6、UITableView能否绑定多个数据源？
 
 答：不能
 
 7、一个UIViewController能否管理多个UITableView ?
 
 答：可以
 
 8、ios4、5、6相对于之前的版本添加了哪些新特性？
 这个就比较多了，比如：抛弃谷歌地图 新推Maps应用 ，大幅加强中国本地化支持，Siri开口讲普通话，通过iCloud体验分享乐趣，Passbook电子票券管理，随时随地的FaceTime，电话功能增强，Safari支持全屏浏览，Mail应用新增VIP，万能辅助：更强大等等了
 
 
 
 
 
 9、同步请求和异步请求什么区别？
 
 
 
 答：发送同步请求，程序将停止用户交互，直至服务器返回数据完成，才可以进行下一步操作，
 
 异步请求不会阻塞主线程，而会建立一个新的线程来操作，用户发出异步请求后，依然可以对UI进行操作，程序可以继续运行。
 
 
 10、iOS中的多线程操作、多线程方式
 
 答：iOS提供了方便的多线程调用机制:NSOperation和NSOperationQueue。它的使用方法也很简单，
 
 一般都是将NSOperation对象加入到NSOperationQueue队列中，加入后队列就开始处理，知道任务操作完成。
 
 11、UIViewController的生命周期
 
 答：当一个视图控制器被创建，并在屏幕上显示的时候。 代码的执行顺序
 // 视图显示在屏幕上的顺序
 
 1、 alloc                    创建对象，分配空间。
 
 2、init (initWithNibName)    初始化对象,初始化数据。
 
 3、loadView                   从nib载入视图, 这一步不需要去干涉。除非没有使用xib文件创建视图。
 
 4、viewDidLoad                加载完毕，可以进行自定义数据以及动态创建其他控件。
 
 5、viewWillAppear             视图将出现在屏幕之前，马上这个视图即将显示在屏幕上。
 
 6、viewDidAppear              视图已在屏幕上渲染完成。
 
 // 视图将被从屏幕上移除的顺序
 
 1、viewWillDisappear          视图将被从屏幕上移除之前执行。
 
 2、viewDidDisappear           视图已经被从屏幕上移除。
 
 3、dealloc                    视图被销毁，此时需要在init和viewDidLoad中创建的对象进行释放。
 
 4、viewDidUnload              出现内存警告在内存不足时执行，并对所有非当前显示的controller执行。
 
 
 
 本视图的所有子视图将被销毁，以释放内存,此时开发者需要手动对viewLoad、viewDidLoad中创建的对象释放内存。
 
 因为当这个视图再次显示在屏幕上的时候，viewLoad、viewDidLoad 再次被调用，以便再次构造视图。
 
 
 
 12、Autorerelease对象什么时候释放？
 
 答：autorelease实际上只是把对release的调用延迟了，对于每一个Autorelease，系统只是把该Object放入了当前的Autorelease pool中，当该pool被释放时，该pool中的所有Object会被调用Release。
 
 
 13、iOS数据持久化方式
 
 答：四种：属性列表、对象归档、SQLite3和Core Data
 
 
 
 14、Object－c的类可以多重继承么？可以实现多个接口么？Category是什么？重写一个类的方式用继承好还是分类好？为什么？
 
 答：Object-c的类不可以多重继承；可以实现多个接口，通过实现多个接口可以完成C++的多重继承；Category是类别，一般情况用分类好，用Category去重写类的方法，仅对本Category有效，不会影响到其他类与原有类的关系。
 
 
 
 15. #import 跟#include 又什么区别，@class呢, ＃import<> 跟 #import”"又什么区别？
 
 答：#import是Objective-C导入头文件的关键字，#include是C/C++导入头文件的关键字,使 用#import头文件会自动只导入一次，不会重复导入，相当于#include和#pragma once；@class告诉编译器某个类的声明，当执行时，才去查看类的实现文件，可以解决头文件的相互包含；#import<>用来包含系 统的头文件，#import””用来包含用户头文件。
 
 
 
 16.属性readwrite，readonly，assign，retain，copy，nonatomic 各是什么作用，在那种情况下用？
 
 答：readwrite 是可读可写特性；需要生成getter方法和setter方法时
 
 readonly 是只读特性  只会生成getter方法 不会生成setter方法 ;不希望属性在类外改变
 
 assign 是赋值特性，setter方法将传入参数赋值给实例变量；仅设置变量时；
 
 retain 表示持有特性，setter方法将传入参数先保留，再赋值，传入参数的retaincount会+1;
 
 copy 表示赋值特性，setter方法将传入对象复制一份；需要完全一份新的变量时。
 
 nonatomic 非原子操作，决定编译器生成的setter getter是否是原子操作，atomic表示多线程安全，一般使用nonatomic
 
 
 
 17.常见的object-c的数据类型有那些， 和C的基本数据类型有什么区别？如：NSInteger和int
 
 答：object-c的数据类型有 NSString，NSNumber，NSArray，NSMutableArray，NSData等等，这些都是class，创建后便是对象，而C语言的基本数据类型int，只是一定字节的内存空间，用于存放数值；而object-c的NSNumber包含有父类NSObject的方法和 NSNumber自己的方法，可以完成复杂的操作。
 
 
 
 18.Objective-C如何对内存管理的,说说你的看法和解决方法?
 
 答：Objective-C的内存管理主要有三种方式ARC（自动内存计数）、手动内存计数、内存池。
 
 解决方法的话： 谁持有，谁释放。
 
 
 
 19.如何对iOS设备进行性能测试?
 
 答：Profile-> Instruments ->Time Profiler
 
 
 
 20.Object C中创建线程的方法是什么？如果在主线程中执行代码，方法是什么？如果想延时执行代码、方法又是什么？
 
 答：线程创建有三种方法：使用NSThread创建、使用 GCD的dispatch、使用子类化的NSOperation,然后将其加入NSOperationQueue;在主线程执行代码，方法是 performSelectorOnMainThread，如果想延时执行代码可以用performSelector:onThread:withObject:waitUntilDone:
 
 
 
 21.描述一下iOS SDK中如何实现MVC的开发模式
 
 答：MVC是：模型--视图--控制  开发模式，对于iOS SDK，所有的View都是视图层的，它应该独立于模型层，由视图控制层来控制。所有的用户数据都是模型层，它应该独立于视图。所有的ViewController都是控制层，由它负责控制视图，访问模型数据。
 
 
 
 22.定义属性时，什么情况使用copy、assign、retain？
 
 答：assign用于简单数据类型，如NSInteger,double,bool, 其实还有后面的block等；
 
 retain和copy用于对象，copy用于当a指向一个对象，b也想指向同样的对象的时候，如果用assign，a如果释放，再调用b会crash,如果用copy 的方式，a和b各自有自己的内存，  就可以解决这个问题。
 
 retain 会使计数器加一，也可以解决assign的问题。
 
 另外：atomic和nonatomic用来决定编译器生成的getter和setter是否为原子操作。在多线程环境下，原子操作是必要的，否则有可能引起错误的结果。
 
 加了atomic，setter函数会变成下面这样：
 
 if (property != newValue) {
 
 [property release];
 
 property = [newValue retain];
 
 }
 
 
 
 23. Object-C有私有方法吗？私有变量呢？
 
 答：objective-c – 类里面的方法只有两种, 静态方法和实例方法，所有实例变量默认都是私有的，所有实例方法默认都是公有的。
 
 
 
 24.浅拷贝和深拷贝区别是什么
 
 答：浅拷贝：只复制指向对象的指针，而不复制引用对象本身。
 
 
 深拷贝：复制引用对象本身。
 
 
 
 25.自动释放池是什么,如何工作
 
 答： 当您向一个对象发送一个autorelease消息时，Cocoa就会将该对 象的一个引用放入到最新的自动释放池。
 
 它仍然是个正当的对象，因此自动释放池定义的作用域内的其它对象可以向它发送消息。当程序执行到作用域结束的位置时，
 
 自动释放池就会被释放，池中的所有对象也就被释放。
 
 
 
 26.单件实例是什么
 
 答： Foundation 和 Application Kit 框架中的一些类只允许创建单件对象，即这些类在当前进程中的唯一实例。
 
 举例：NSFileManager 和NSWorkspace类在使用时都是基于进程进行单件对象的实例化。
 
 当向这些类请求实例的时候，它们会向您传递单一实例的一个引用，如果该实例还不存在，则首先进行实例的分配 和初始化。
 
 
 
 27.类别的作用？继承和类别在实现中有何区别？
 答：category 可以在不获悉，不改变原来代码的情况下往里面添加新的方法，只能添加，不能删除修改。
 
 并且如果类别和原来类中的方法产生名称冲突，则类别将覆盖原来的方法，因为类别具有更高的优先级。
 类别主要有3个作用：
 
 
 (1)将类的实现分散到多个不同文件或多个不同框架中。
 
 (2)创建对私有方法的前向引用。
 
 
 (3)向对象添加非正式协议。
 
 
 继承可以增加，修改或者删除方法，并且可以增加属性。
 
 
 
 28.类别和类扩展的区别。
 答：category和extensions的不同在于 后者可以添加属性。另外后者添加的方法是必须要实现的。
 extensions可以认为是一个私有的Category。
 
 
 
 29.KVO and KVC?
 
 答：kvc:键 - 值编码是一种间接访问对象的属性，使用字符串来标识属性，而不是通过调用存取方法，直接或通过实例变量访问的机制。
 很多情况下可以简化程序代码。apple文档其实给了一个很好的例子。
 kvo:键值观察机制，他提供了观察某一属性变化的方法，极大的简化了代码。
 具体用看到用到过的一个地方是对于按钮点击变化状态的的监控。
 比如我自定义的一个button
 [cpp]
 
 
 [self addObserver:self forKeyPath:@"highlighted" options:0 context:nil];
 
 
 
 #pragma mark KVO
 
 
 
 - (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
 {
 
 
 if ([keyPath isEqualToString:@"highlighted"] ) {
 
 
 [self setNeedsDisplay];
 
 
 }
 
 }
 
 对于系统是根据keypath去取的到相应的值发生改变，理论上来说是和kvc机制的道理是一样的。
 对于kvc机制如何通过key寻找到value：
 “当通过KVC调用对象时，比如：[self valueForKey:@”someKey”]时，程序会自动试图通过几种不同的方式解析这个调用。首先查找对象是否带有 someKey 这个方法，如果没找到，会继续查找对象是否带有someKey这个实例变量（iVar），如果还没有找到，程序会继续试图调用
 
 -(id) valueForUndefinedKey:这个方法。如果这个方法还是没有被实现的话，程序会抛出一个NSUndefinedKeyException异常错误。
 
 
 
 
 
 (cocoachina.com注：Key-Value Coding查找方法的时候，不仅仅会查找someKey这个方法，还会查找getsomeKey这个方法，前面加一个get，或者_someKey以及_getsomeKey这几种形式。同时，查找实例变量的时候也会不仅仅查找someKey这个变量，也会查找_someKey这个变量是否存在。）
 
 设计valueForUndefinedKey:方法的主要目的是当你使用-(id)valueForKey方法从对象中请求值时，对象能够在错误发生前，有最后的机会响应这个请求。这样做有很多好处，下面的两个例子说明了这样做的好处。“
 来至cocoa，这个说法应该挺有道理。
 
 
 因为我们知道button却是存在一个highlighted实例变量.因此为何上面我们只是add一个相关的keypath就行了，
 
 
 可以按照kvc查找的逻辑理解，就说的过去了。
 
 
 
 30.代理的作用？
 
 答：代理的目的是改变或传递控制链。允许一个类在某些特定时刻通知到其他类，而不需要获取到那些类的指针。可以减少框架复杂度。
 另外一点，代理可以理解为java中的回调监听机制的一种类似。
 
 
 
 31.说说响应链
 
 答： 事件响应链。包括点击事件，画面刷新事件等。在视图栈内从上至下，或者从下之上传播。
 
 
 
 32.frame和bounds有什么不同？
 
 答：frame指的是：该view在父view坐标系统中的位置和大小。（参照点是父亲的坐标系统）
 bounds指的是：该view在本身坐标系统中 的位置和大小。（参照点是本身坐标系统）
 
 
 
 33.方法和选择器有何不同？
 
 答：selector是一个方法的名字，method是一个组合体。
 
 
 
 34.Object－c的类可以多重继承么？可以实现多个接口么？重写一个类的方式用继承好还是分类好？为什么？
 
 答：Objective-c只支持单继承，如果要实现多继承的话，可以通过类别和协议的方式来实现，cocoa 中所有的类都是NSObject 的子类，多继承在这里是用protocol 委托代理 来实现的。
 
 
 
 35.ARC自动引用技术
 
 答:1.ARC是编译特性，不是运行时特性，只是在编译的时候，编译器会自动加上释放代码
 
 2.不能调用release、retain、autorelease、retainCount
 
 3.dealloc注意
 
 1> 不能在dealloc中调用[super dealloc]
 
 2> 不能在dealloc中释放资源
 
 4.@property参数说明
 
 1> retain 改为 strong
 
 2> 基本数据类型(int\float)还是用assign
 
 3> copy 还是 copy
 
 4> 如果2个对象循环引用，一端用strong，一端用weak
 
 5> weak是用在对象上，weak其实作用跟assign相当
 
 5.ARC中只允许使用通过@autoreleasepool {}创建自动释放池
 
 
 
 36 GCD技术
 
 答:Grand Central Dispatch简称GCD 解决多核并行运算的一种方案
 
 看代码就行：
 
 //  Grand Central Dispatch简称GCD技术
 
 
 
 // Do any additional setup after loading the view.
 
 
 
 //    dispatch_queue_t newDispath = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
 
 //    dispatch_async(newDispath, ^{
 
 //        [self downloadImage];
 
 //    });
 
 
 
 //    #defineDISPATCH_QUEUE_PRIORITY_HIGH  2
 
 //    #defineDISPATCH_QUEUE_PRIORITY_DEFAULT  0
 
 //    #defineDISPATCH_QUEUE_PRIORITY_LOW (-2)
 
 //    #defineDISPATCH_QUEUE_PRIORITY_BACKGROUNDINT16_MIN
 
 
 
 
 
 
 
 
 
 dispatch queue分为下面三种：
 
 * Serial:又称为private dispatch queues，同时只执行一个任务。Serial queue通常用于同步访问特定的资源或数据。当你创建多   个        Serial queue时，虽然它们各自是同步执行的，但Serial queue与Serial queue之间是并发执行的。
 
 * Concurrent: 又称为global dispatch queue，可以并发地执行多个任务，但是执行完成的顺序是随机的。
 
 * Main dispatch queue它是全局可用的serial queue，它是在应用程序主线程上执行任务的
 




//  一般GCD 可以如下操作



dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0), ^{
    
    // 耗时的操作
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        // 更新界面
        
    });
    
});



[selfexampleDispatch];




 
 *系统给每一个应用程序提供了三个concurrent dispatch queues。
 
 *这三个并发调度队列是全局的，它们只有优先级的不同。
 
 *因为是全局的，我们不需要去创建。我们只需要通过使用函数dispath_get_global_queue去得到队列
 




dispatch_queue_t globalQ =dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0);



NSLog(@"global:%p",globalQ);

dispatch_queue_t mainQ =dispatch_get_main_queue();

NSLog(@"mainQ:%p",mainQ);


 
 *虽然dispatch queue是引用计数的对象，但是以上两个都是全局的队列，不用retain或release。
 









 
 *dispatch_group_async可以实现监听一组任务是否完成，完成后得到通知执行其他的操作。
 
 *这个方法很有用，比如你执行三个下载任务，当三个任务都下载完成后你才通知界面说完成的了。
 


timeInt = 0;

[NSTimerscheduledTimerWithTimeInterval:1
 
                                target:self
 
                              selector:@selector(checkingTime)
 
                              userInfo:nil
 
                               repeats:YES];

[selfexampleDispath_group];





dispatch_barrier_async的使用
 
 *dispatch_barrier_async是在前面的任务执行结束后它才执行，而且它后面的任务等它执行完成之后才会执行
 




[selfexampleDispatch_barrier];





dispatch_apply
 
 *执行某个代码片段N次。
 


dispatch_apply(5, globalQ, ^(size_t index) {
    
    // 执行5次
    
});
 
 
 








 */

@end
