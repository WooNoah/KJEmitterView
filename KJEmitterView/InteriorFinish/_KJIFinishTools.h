//
//  KJInteriorFinishTools.h
//  KJEmitterView
//
//  Created by 杨科军 on 2020/5/20.
//  Copyright © 2020 杨科军. All rights reserved.
//  装修公共方法类

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import <Accelerate/Accelerate.h>

NS_ASSUME_NONNULL_BEGIN
/// 图片扭曲之后的参数
typedef struct KJImageWarpResult {
    UIImage*newImage;/// 扭曲后图片
    CGRect  newRect; /// 扭曲后尺寸
}KJImageWarpResult;
/// 透视选区四点
typedef struct KJKnownPoints {
    CGPoint PointA;
    CGPoint PointB;
    CGPoint PointC;
    CGPoint PointD;
}KJKnownPoints;
/// 滑动方向
typedef NS_ENUM(NSInteger, KJSlideDirectionType) {
    KJSlideDirectionTypeLeftBottom, /// 左下
    KJSlideDirectionTypeRightBottom,/// 右下
    KJSlideDirectionTypeRightTop,   /// 右上
    KJSlideDirectionTypeLeftTop,    /// 左上
};
/// 手势移动方向
typedef NS_ENUM(NSInteger, KJPanMoveDirectionType) {
    KJPanMoveDirectionTypeNoMove = 0,/// 没有移动
    KJPanMoveDirectionTypeTop,   /// 向上
    KJPanMoveDirectionTypeBottom,/// 向下
    KJPanMoveDirectionTypeLeft,  /// 向左
    KJPanMoveDirectionTypeRight, /// 向右
};
/// 图片指定区域
typedef NS_ENUM(NSInteger, KJImageAppointType) {
    KJImageAppointTypeCustom,   /// 自定义区域，需要传入指定frame
    KJImageAppointTypeTop21,    /// 顶部二分之一
    KJImageAppointTypeCenter21, /// 中间二分之一
    KJImageAppointTypeBottom21, /// 底部二分之一
    KJImageAppointTypeTop31,    /// 顶部三分之一
    KJImageAppointTypeCenter31, /// 中间三分之一
    KJImageAppointTypeBottom31, /// 底部三分之一
    KJImageAppointTypeTop41,    /// 顶部四分之一
    KJImageAppointTypeCenter41, /// 中间四分之一
    KJImageAppointTypeBottom41, /// 底部四分之一
    KJImageAppointTypeTop43,    /// 顶部四分之三
    KJImageAppointTypeCenter43, /// 中间四分之三
    KJImageAppointTypeBottom43, /// 底部四分之三
};
@interface _KJIFinishTools : NSObject

#pragma mark - 逻辑处理
/// 判断手势方向
+ (KJPanMoveDirectionType)kj_moveDirectionWithTranslation:(CGPoint)translation;
/// 确定滑动方向
+ (KJSlideDirectionType)kj_slideDirectionWithPoint:(CGPoint)point Point2:(CGPoint)point2;
/// 不同滑动方向转换为正确透视区域四点
+ (KJKnownPoints)kj_pointsWithKnownPoints:(KJKnownPoints)knownPoints BeginPoint:(CGPoint)beginPoint EndPoint:(CGPoint)endPoint DirectionType:(KJSlideDirectionType)directionType;
/// 平移之后透视点相对处理
+ (KJKnownPoints)kj_changePointsWithKnownPoints:(KJKnownPoints)points Translation:(CGPoint)translation;
/// 判断当前点是否在路径选区内
+ (bool)kj_confirmCurrentPointWithPoint:(CGPoint)point BezierPath:(UIBezierPath*)path;
/// 判断当前点是否在已知四点选区内
+ (bool)kj_confirmCurrentPointWithPoint:(CGPoint)point KnownPoints:(KJKnownPoints)points;
/// 判断当前点是否在Rect内
+ (bool)kj_confirmCurrentPointWithPoint:(CGPoint)point Rect:(CGRect)rect;
/// 获取对应的Rect
+ (CGRect)kj_rectWithPoints:(KJKnownPoints)points;
#pragma mark - 几何方程式
/// 已知A、B两点和C点到B点的长度，求垂直AB的C点
+ (CGPoint)kj_perpendicularLineDotsWithPoint1:(CGPoint)A Point2:(CGPoint)B VerticalLenght:(CGFloat)len Positive:(BOOL)pos;
/// 已知A、B、C、D 4个点，求AB与CD交点  备注：重合和平行返回（0,0）
+ (CGPoint)kj_linellaeCrosspointWithPoint1:(CGPoint)A Point2:(CGPoint)B Point3:(CGPoint)C Point4:(CGPoint)D;
/// 求两点线段长度
+ (CGFloat)kj_distanceBetweenPointsWithPoint1:(CGPoint)A Point2:(CGPoint)B;
/// 已知A、B、C三个点，求AB线对应C的平行线上的点  y = kx + b
+ (CGPoint)kj_parallelLineDotsWithPoint1:(CGPoint)A Point2:(CGPoint)B Point3:(CGPoint)C;
/// 椭圆求点方程
+ (CGPoint)kj_ovalPointWithRect:(CGRect)lpRect Angle:(CGFloat)angle;
#pragma mark - 图片处理
/// 获取图片指定区域
+ (UIImage*)kj_getImageAppointAreaWithImage:(UIImage*)image ImageAppointType:(KJImageAppointType)type CustomFrame:(CGRect)rect;
/// 旋转图片和镜像处理 orientation 图片旋转方向
+ (UIImage*)kj_rotationImageWithImage:(UIImage*)image Orientation:(UIImageOrientation)orientation;
/** 任意角度图片旋转 */
+ (UIImage*)kj_rotateImage:(UIImage*)image Radians:(CGFloat)radians;
/// 图片围绕任意点旋转任意角度
+ (UIImage*)kj_rotateImage:(UIImage*)image Rotation:(CGFloat)rotation Point:(CGPoint)point;
/// 矩形图扭曲变形成椭圆弧形图
+ (UIImage*)kj_orthogonImageBecomeOvalWithImage:(UIImage*)image Rect:(CGRect)rect Margin:(bool)margin;
//+ (KJImageWarpResult)changeImageByPoints:(NSArray*)pointArray Image:(UIImage*)image;
@end

NS_ASSUME_NONNULL_END
