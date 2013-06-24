//
//  main.m
//  gcdpp-run
//
//  Created by Sergey Sergeev on 6/24/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include <UIKit/UIKit.h>
#include "gtest/gtest.h"
#include "AppDelegate.h"

int main(int argc, char *argv[])
{
    @autoreleasepool {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout<<RUN_ALL_TESTS()<<std::endl;
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
