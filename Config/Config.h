#pragma once
#include "../ImGui/CustomWidgets.h"
namespace Config {

    inline bool 加载一次参数 = false;
    inline bool 重新登录 = true;
    inline float screenScale = 2;

    /*personal*/
    inline bool 实名认证 = false;
    inline bool 上帝视角 = false;
    inline bool 广告奖励 = false;
    inline bool 无视碰撞 = false;
    inline bool 炫跑卡 = false;
    inline bool 解锁角色 = false;
    inline bool 解锁滑板 = false;
    inline bool 解锁背饰 = false;
    inline bool 解锁主题 = false;
    inline bool 解锁sticker = false;
    inline bool 修改重力 = false;
    inline float 重力修改为 = 200.f;
    inline bool 始终可以跳跃 = false;

    /*PVP*/
    inline bool 始终拿好道具 = false;
    inline bool 命中最近目标 = false;
    inline bool 始终举报 = false;
    inline bool 十倍举报 = false;
    inline bool 修改昵称 = false;
    inline bool 修改排名 = false;
    inline int 修改排名为 = 100;
    inline std::string 修改昵称为 = "";
    inline bool 无视道具 = false;
    inline bool 双倍充能 = false;
    inline bool 自动充能 = false;
    inline bool 疯狂加速 = false;
    inline bool 自定义消息内容 = false;
    inline std::string 要发送的消息内容 = "";
    inline bool 修改速度 = false;
    inline float 速度修改为 = 8.0f;
    inline bool 自动使用滑板= false;
    inline float 使用滑板距离 = 5.f;
    inline bool 防作弊合法化 = false;
    inline bool 正在休眠防作弊 = false;

    /*Modify*/
    inline bool 修改金币 = false;
    inline int 修改成多少金币 = 10;
    inline bool 修改钥匙 = false;
    inline int 修改成多少钥匙 = 10;
    inline bool 修改宝物钥匙 = false;
    inline int 修改成多少宝物钥匙 = 10;
    
    /*Util*/
    inline bool 修改分数 = false;
    inline int 修改成多少分 = 10;
    inline bool 修改模型大小 = false;
    inline float 模型大小倍率 = 1.0;
    inline bool 合法提示 = false;

    /*visual*/
    inline bool 显示已开启功能 = false;
    inline bool 显示方框 = false;
}