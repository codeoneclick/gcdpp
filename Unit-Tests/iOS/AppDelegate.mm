//
//  AppDelegate.m
//  gcdpp-run
//
//  Created by Sergey Sergeev on 6/24/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include "AppDelegate.h"
#include "gcdpp.h"

@implementation AppDelegate

class C
{
public:
    int a;
};

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    std::function<void(int, float, std::string)> function1 = [](int a, float b, const std::string& c)
    {
        std::cout<<"call"<<a<<b<<c<<std::endl;
    };
    
    std::function<void(std::string)> function2 = [](std::string a)
    {
        std::cout<<"call"<<a<<std::endl;
    };
    
    C* param = new C();
    param->a = 99;
    
    std::function<void(C*)> function3 = [](C* a)
    {
        std::cout<<"call"<<a->a<<std::endl;
    };
    
    std::shared_ptr<C> param2 = std::make_shared<C>();
    param->a = 101;
    
    std::function<void(std::shared_ptr<C> )> function4 = [](std::shared_ptr<C> a)
    {
        std::cout<<"call"<<a->a<<std::endl;
    };
    
    std::function<void(void)> function5 = [](void)
    {
        std::cout<<"void"<<std::endl;
    };
    
    gcdpp::gcdpp_dispatch_async(gcdpp::gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH), function5);
    
    
    gcdpp::gcdpp_dispatch_async<int, float, std::string>(gcdpp::gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH), function1, 1, 2.0f, "Hello World");
    gcdpp::gcdpp_dispatch_async<std::string>(gcdpp::gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH), function2, "two");
    gcdpp::gcdpp_dispatch_async<C*>(gcdpp::gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH), function3, param);
    gcdpp::gcdpp_dispatch_async<std::shared_ptr<C>>(gcdpp::gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH), function4, param2);
    
    return YES;
}


@end
