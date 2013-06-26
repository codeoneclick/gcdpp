//
//  MainLib.m
//  gcdpp-run
//
//  Created by Sergey Sergeev on 6/24/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include "MainLib.h"
#include "gcdppLib.h"
#include "gtest/gtest.h"

@implementation MainLib


std::queue<std::packaged_task<void()>> queue;

template<class FUNCTION, class ...ARGS>
std::future<typename std::result_of<FUNCTION(ARGS...)>::type>
dispatch(FUNCTION &&f, ARGS &&...args) {
    std::packaged_task<typename std::result_of<FUNCTION(ARGS...)>::type()> task(std::bind(f,args...));
    auto future = task.get_future();
    queue.push(std::packaged_task<void()>(std::move(task)));
    return future;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    std::thread::id this_id = std::this_thread::get_id();
    std::cout <<"[Main] thread : "<<this_id<<std::endl;
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    NSMethodSignature* signature = [self methodSignatureForSelector:@selector(onTick:)];
    NSInvocation* invocation = [NSInvocation invocationWithMethodSignature:signature];
    [invocation setTarget: self];
    [invocation setSelector:@selector(onTick:)];
    
    NSTimer *sender = [NSTimer timerWithTimeInterval:0.1 invocation:invocation repeats:YES];
    NSRunLoop *runner = [NSRunLoop currentRunLoop];
    [runner addTimer:sender forMode:NSDefaultRunLoopMode];
    
    std::function<void(int, float, std::string)> function = [](int a, float b, const std::string& c)
    {
        EXPECT_TRUE(a == 1 && b == 2.0f && c == "Hello World");
    };
    
    auto future = dispatch(std::move(function), 1, 2.0f, "Hello World");
    
    queue.back()();
    
    std::cout<<"[Testing] "<<std::endl<<RUN_ALL_TESTS()<<std::endl;
    
    return YES;
}

- (void)onTick:(NSTimer*)sender
{
    gcdpp::impl::UpdateMainQueue();
}

@end

