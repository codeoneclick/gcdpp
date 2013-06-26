//
//  main.m
//  gcdpp-run
//
//  Created by Sergey Sergeev on 6/24/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include <UIKit/UIKit.h>
#include "gtest/gtest.h"
#include "MainLib.h"

int main(int argc, char *argv[])
{
    @autoreleasepool
    {
        ::testing::InitGoogleTest(&argc, argv);
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([MainLib class]));
    }
}
