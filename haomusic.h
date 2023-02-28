﻿#ifndef HAOMUSIC_H
#define HAOMUSIC_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QListWidgetItem>
#include <QSystemTrayIcon>

#include <QUrl>
#include <QPixmap>
#include <QSize>

#include <QGraphicsDropShadowEffect>
#include "music.h"
#include "myhttp.h"
#include "customitem.h"


QT_BEGIN_NAMESPACE
namespace Ui { class HaoMusic; }
QT_END_NAMESPACE

class HaoMusic : public QWidget
{
    Q_OBJECT

public:
    HaoMusic(QWidget *parent = nullptr);
    ~HaoMusic();
    static HaoMusic* getInstance();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::HaoMusic    *ui;
    QMediaPlaylist  *mediaPlaylist      = nullptr;  // 媒体播放列表
    QMediaPlayer    *mediaPlayer        = nullptr;  // 媒体播放器
    MyHttp          *search             = nullptr;  // 网络搜索
    CustomItem      *currentPlayingItem = nullptr;  // 当前正在播放的item

    QPoint  m_mousePoint;       // 鼠标坐标
    QPoint  movePoint;          // 窗口移动距离
    bool    mousePress = false; // 鼠标左键是否按下
    int     itemType = 100;

    int     offset          = 0;    // 搜索偏移量
    int     volume          = 50;   // 音量
    int     currentLrcRow   = 1;    // 当前歌词所在行
    int     loadingTimes    = 2000; // 加载所需事件（ms）
    QString searchKeywords  = "";   // 搜索关键词
    QMovie *loadingMovie;           // 加载动画
    Music   currentMusic;           // 当前播放的音乐

    QListWidgetItem     *currentLrcItem;        // 当前歌词所在item
    QMap<int,QString>    lrcMap;                // 歌词
    QList<int>           lrcKeys;               // 歌词对应的时间帧
    QList<Music>         musicList;             // 播放列表音乐列表
    QList<Music>         searchResultMusicList; //搜索结果音乐列表
    QList<Music>         favoriteMusicList;     // 我喜欢的音乐
    // 绘制圆角阴影窗口
    void paintShadowRadiusWidget();
    // 设置托盘图标
    void setTrayIcon();
    // 初始化播放器
    void initPlayer();
    // 连接信号和槽
    void connectSignalsAndSlots();
    // 音乐进度条点击事件处理函数
    void sliderClicked();
    // 显示搜索结果
    void showSearchResult();
    // 更新播放列表
    void updateMediaPlaylist();
    // 更新底部栏音乐信息
    void updateBottomMusicInfo();
    // 更新布局
    void updateLayout();
    // 显示歌词
    void showLrc();
    // 歌词滚动
    void lrcRoll(int position);
    // 显示加载界面
    void showLoadingPage();
    // 更改当前播放项的样式
    void changeCurrentPlayingItem(CustomItem *item);
    // 播放当前项
    void playingTheItem(CustomItem *item);
    // 显示歌词页面
    void showLrcPage();
    // 显示所有我喜欢的音乐
    void showMyFavoriteMusicList();
    // 双击列表项
    void onCustomItemDoubleClicked(CustomItem *item);

private slots:
    void iconActived(QSystemTrayIcon::ActivationReason);

    void on_pushButton_close_clicked();

    void on_pushButton_maxsize_clicked();

    void on_pushButton_minsize_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_lastsong_clicked();

    void on_pushButton_switch_clicked();

    void on_pushButton_nextsong_clicked();

    void on_pushButton_mode_clicked();

    void on_pushButton_volume_clicked();

    void onPositionChanged(qint64);

    void onDurationChanged(qint64);

    void on_horizontalSlider_volume_valueChanged(int value);

    void on_pushButton_recentlyplayed_clicked();

    void on_pushButton_defaultSongList_clicked();

    void on_pushButton_localmusic_clicked();

    void on_pushButton_dropDown_clicked();

    void on_pushButton_favorite_clicked();

    // 右键菜单点击事件
    void menuPlayMusicClicked(CustomItem *item);

    void menuAddToMyFavoriteClicked(CustomItem *item);

    void menuAddToSonglistClicked(CustomItem *item);

    void on_listWidget_lrc_itemClicked(QListWidgetItem *item);

    void on_lineEdit_search_textChanged(const QString &arg1);
};

#endif // HAOMUSIC_H
