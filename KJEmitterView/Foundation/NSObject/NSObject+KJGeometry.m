//
//  NSObject+KJGeometry.m
//  KJEmitterView
//
//  Created by 杨科军 on 2020/5/13.
//  Copyright © 2020 杨科军. All rights reserved.
//

#import "NSObject+KJGeometry.h"

@implementation NSObject (KJGeometry)

/// 已知A、B两点和C点到B点的长度，求垂直AB的C点
+ (CGPoint)kj_perpendicularLineDotsWithA:(CGPoint)A B:(CGPoint)B Len:(CGFloat)len Positive:(BOOL)positive{
    return kj_perpendicularLineDots(A,B,len,positive);
}
static inline CGPoint kj_perpendicularLineDots(CGPoint A, CGPoint B, CGFloat len, BOOL positive){
    CGFloat x1 = A.x,y1 = A.y;
    CGFloat x2 = B.x,y2 = B.y;
    CGFloat k1 = 0,k = 0;
    if (x1 == x2) {
        k1 = -1;/// 垂直线
        k = 1;
    }else if (y1 == y2) {
        k1 = 1;/// 水平线
        k = -1;
    }else{
        k1 = (y1-y2)/(x1-x2);
        k = -1/k1;
    }
    CGFloat b = y2 - k*x2;
    /// 根据 len² = (x-x2)² + (y-y2)²  和  y = kx + b 推倒出x、y
    CGFloat t = k*k + 1;
    CGFloat g = k*(b-y2) - x2;
    CGFloat f = x2*x2 + (b-y2)*(b-y2);
    CGFloat m = g/t;
    CGFloat n = (len*len - f)/t + m*m;
    
    CGFloat xa = sqrt(n) - m;
    CGFloat ya = k * xa + b;
    CGFloat xb = -sqrt(n) - m;
    CGFloat yb = k * xb + b;
    if (positive) {
        return yb>ya ? CGPointMake(xb, yb) : CGPointMake(xa, ya);
    }else{
        return yb>ya ? CGPointMake(xa, ya) : CGPointMake(xb, yb);
    }
    return CGPointZero;
}

/// 已知A、B、C、D 4个点，求AB与CD交点  备注：重合和平行返回（0,0）
+ (CGPoint)kj_linellaeCrosspointWithA:(CGPoint)A B:(CGPoint)B C:(CGPoint)C D:(CGPoint)D{
    return kj_linellaeCrosspoint(A,B,C,D);
}
static inline CGPoint kj_linellaeCrosspoint(CGPoint A,CGPoint B,CGPoint C,CGPoint D){
    CGFloat x1 = A.x,y1 = A.y;
    CGFloat x2 = B.x,y2 = B.y;
    CGFloat x3 = C.x,y3 = C.y;
    CGFloat x4 = D.x,y4 = D.y;
    
    CGFloat k1 = (y1-y2)/(x1-x2);
    CGFloat k2 = (y3-y4)/(x3-x4);
    CGFloat b1 = y1-k1*x1;
    CGFloat b2 = y4-k2*x4;
    if (x1==x2&&x3!=x4) {
        return CGPointMake(x1, k2*x1+b2);
    }else if (x3==x4&&x1!=x2){
        return CGPointMake(x3, k1*x3+b1);
    }else if (x3==x4&&x1==x2){
        return CGPointMake(0, 0);
    }else{
        if (y1==y2&&y3!=y4) {
            return CGPointMake((y1-b2)/k2, y1);
        }else if (y3==y4&&y1!=y2){
            return CGPointMake((y4-b1)/k1, y4);
        }else if (y3==y4&&y1==y2){
            return CGPointMake(0, 0);
        }else{
            if (k1==k2){
                return CGPointMake(0, 0);
            }else{
                CGFloat x = (b2-b1)/(k1-k2);
                CGFloat y = k2*x+b2;
                return CGPointMake(x, y);
            }
        }
    }
}
/// 求两点线段长度
+ (CGFloat)kj_distanceBetweenPointsWithA:(CGPoint)A B:(CGPoint)B{
    return kj_distanceBetweenPoints(A,B);
}
static inline CGFloat kj_distanceBetweenPoints(CGPoint point1,CGPoint point2) {
    CGFloat deX = point2.x - point1.x;
    CGFloat deY = point2.y - point1.y;
    return sqrt(deX*deX + deY*deY);
};
/// 已知A、B、C三个点，求AB线对应C的平行线上的点  y = kx + b
+ (CGPoint)kj_parallelLineDotsWithA:(CGPoint)A B:(CGPoint)B C:(CGPoint)C{
    return kj_parallelLineDots(A,B,C);
}
static inline CGPoint kj_parallelLineDots(CGPoint A,CGPoint B,CGPoint C){
    CGFloat x1 = A.x,y1 = A.y;
    CGFloat x2 = B.x,y2 = B.y;
    CGFloat x3 = C.x,y3 = C.y;
    CGFloat k = 0;
    if (x1 == x2) k = 1;/// 水平线
    k = (y1-y2)/(x1-x2);
    CGFloat b = y3 - k*x3;
    CGFloat x = x1;
    CGFloat y = k * x + b;/// y = kx + b
    return CGPointMake(x, y);
}

@end
