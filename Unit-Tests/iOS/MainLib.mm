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

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
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
    
    std::cout<<"[Testing] "<<std::endl<<RUN_ALL_TESTS()<<std::endl;
    
    return YES;
}

- (void)onTick:(NSTimer*)sender
{
    gcdpp::impl::UpdateMainQueue();
}

@end

