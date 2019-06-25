# Source code of "Node.js: Let's Write a Dozen of C++ Add-ons"

![Cover](cover.jpg)

[中文文档](README.md)

This repo is the source code of book "Node.js: Let's Write a Dozen of C++ Add-ons" which is written by XadillaX. Enjoy
it!

> **Hint:** All code in this repo were verified under macOS terminal and Node.js 6.x. Theoretically, it may run on
> Windows and UNIX. But I didn't verify for these two platforms.

## Download

You may download the source code from [Brandview official website](http://www.broadview.com.cn/). [Git](https://git-scm.com/) is more recommended if you are familiar with it.

If you're going to clone this repo, use the command line below:

```shell
$ git clone https://github.com/XadillaX/nyaa-nodejs-demo.git --recurse-submodules
```

> Parameter `--recurse-submodules` allows you clone the repo with all submodules.
>
> Due to the feature of GitHub, The ZIP file which downloaded from this page of GitHub will not contain the necessary
> submodules. If you want to get the source code from the method of "Downloading", please go to the official website of
> Brandview.

## Quick Navigation

1. [first build](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/1.%20first%20build)：「1.4.2. node-gyp」
2. [cpp entry](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/2.%20cpp%20entry)：「2.2.2. Node.js Module Loading Principle」
3. [function template](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/3.%20function%20template)：「3.6.1. Function Template」
4. [object template](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/4.%20object%20template)：「3.6.2. Object Template」
5. [object template accessor](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/5.%20object%20template%20accessor)：「3.6.3. Accessor and Interceptor of Object Template」
6. [mapped property interceptor](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/6.%20mapped%20property%20interceptor)：「3.6.3. Accessor and Interceptor of Object Template」
7. [indexed property interceptor](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/7.%20indexed%20property%20interceptor)：「3.6.3. Accessor and Interceptor of Object Template」
8. [internal field wrong](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/8.%20internal%20field%20wrong)：「3.6.4. Internal Field of Object Template」
9. [internal field right](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/9.%20internal%20field%20right)：「3.6.4. Internal Field of Object Template」
10. [function template inherit](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/10.%20function%20template%20inherit)：「3.6.5. Inherit of Object Template」
11. [array prototype map](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/11.%20array%20prototype%20map)：「3.7.6. Function」
12. [try catch](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/12.%20try%20catch)：「3.8.1. Try-Catch」
13. [hello world again](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/13.%20hello%20world%20again)：「4.2.1. Hello World Again」
14. [function parameters](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/14.%20function%20parameters)：「4.2.2. Function Parameters」
15. [run callback](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/15.%20run%20callback)：「4.2.3. Callback Function」
16. [object factory](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/16.%20object%20factory)：「4.2.4. Return an Objects」
17. [function factory](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/17.%20function%20factory)：「4.2.5. Return a Function」
18. [myobject](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/18.%20myobject)：「4.3.1. JavaScript Class C++ Wrapper」
19. [at_exit_hook](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/19.%20at_exit_hook)：「4.3.4. at_exit_hook」
20. [nan echo](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/20.%20nan%20echo)：「5.2.3. Come Come Go!」
21. [nan array prototype map](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/21.%20nan%20array%20prototype%20map)：「5.2.4. Basic Helpers and Macros」
22. [nan set method](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/22.%20nan%20set%20method)：「5.3.3. Setting Method」
23. [nan reverse string](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/23.%20nan%20reverse%20string)：「5.4.3. Play with Data Object」
24. [nan object demo](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/24.%20nan%20object%20demo)：「5.4.3. Play with Data Object」
25. [nan array demo](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/25.%20nan%20array%20demo)：「5.4.3. Play with Data Object」
26. [nan json](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/26.%20nan%20json)：「5.4.3. Play with Data Object」
27. [nan buffer](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/27.%20nan%20buffer)：「5.4.3. Play with Data Object」
28. [nan nbodies](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/28.%20nan%20nbodies)：「5.5.3. Nan::AsyncWorker」
29. [nan dummy download](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/29.%20nan%20dummy%20download)：「5.5.4. Nan::AsyncProgressWorker」
30. [libuv idle](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/30.%20libuv%20idle)：「6.1.3. Have a Taste」
31. [libuv sleep sort](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/31.%20libuv%20sleep%20sort)：「6.2.1. libuv Thread」
32. [libuv sleep sort advanced](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/32.%20libuv%20sleep%20sort%20advanced)：「6.2.2. Synchronization Primitives」
33. [libuv watchdog](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/33.%20libuv%20watchdog)：「6.3.2. Semi-finished Watchdog」
34. [efsw](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/34.%20efsw)：「7.1.1. Functional Planning」
35. [efsw advanced](https://github.com/XadillaX/node-efsw/tree/85cc5b816c3e04b4df92f63592f5e9ce99808418)：「7.4.2. JavaScript Code Improving」
36. [napi](https://github.com/XadillaX/nyaa-nodejs-demo/tree/master/36.%20napi)：「9.1.1. Write a `Echo` Function」

## Purchase Link of Book

+ [JD](https://item.jd.com/12380404.html)
+ [Tmall](https://detail.tmall.com/item.htm?id=571628730908&cat_id=2)
+ [Dangdang](http://product.dangdang.com/25291814.html)
+ [Amazon](https://www.amazon.cn/dp/B07DL8GHQC/ie=UTF8&qid=1528969734)
+ [china-pub](http://product.china-pub.com/8039217)
+ [Douban](https://book.douban.com/subject/30247892/)

## QQ Communicate Group

<img src="./qq_group.jpg" width="200" alt="QQ 群" />

## Thanks

Thank you for supporting my book!

![フランドール・スカーレット](flandre.jpg)

<center><font color="gray"><small>This picture from <a target="_blank" href="https://www.pixiv.net/member_illust.php?mode=medium&illust_id=35873732">Pixiv</a></small></font></center>
