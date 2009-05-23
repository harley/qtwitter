/***************************************************************************
 *   Copyright (C) 2008-2009 by Dominik Kapusta       <d@ayoy.net>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of      *
 *   the License, or (at your option) any later version.                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to                     *
 *   the Free Software Foundation, Inc.,                                   *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef TWEETMODEL_H
#define TWEETMODEL_H

#include <QStandardItemModel>
#include <QPointer>
#include <twitterapi/twitterapi.h>

class QPixmap;
class QUrl;
class Tweet;
class ThemeData;
class TweetModel;
class StatusListView;
class StatusList;
struct Status;

class TweetModel : public QStandardItemModel
{
//  typedef TwitterAPI::SocialNetwork SocialNetwork;

  Q_OBJECT
//  Q_PROPERTY( SocialNetwork network READ getNetwork WRITE setNetwork )
//  Q_PROPERTY( QString login READ getLogin WRITE setLogin )

public:

  enum TweetState {
    STATE_UNREAD,
    STATE_READ,
    STATE_ACTIVE
  };

  TweetModel( int margin, StatusListView *parentListView, QObject *parent = 0 );
  ~TweetModel();

  Tweet* currentTweet();
  void deselectCurrentIndex();
  void setTheme( const ThemeData &theme );
  void setStatusList( StatusList *statusList );
  void setMaxTweetCount( int count );
  void populate();
//  void setVisible( bool isVisible );
//  void display();
//  void clear();

public slots:
//  void insertTweet( Entry *entry );
//  void deleteTweet( int id );
  void updateDisplay( int ind );
  void sendDeleteRequest( int id );
  void selectTweet( const QModelIndex &index );
  void selectTweet( Tweet *tweet );
  void markAllAsRead();
  void checkForUnread();
  void retranslateUi();
  void resizeData( int width, int oldWidth );
  void moveFocus( bool up );
  void setImageForUrl( const QString& url, QPixmap *image );

signals:
  void retweet( QString message );
  void destroy( TwitterAPI::SocialNetwork, const QString &login, int id );
  void newTweets( const QString &login, bool exists );
  void openBrowser( QUrl address );
  void reply( const QString &name, int inReplyTo );
  void about();

private slots:
  void emitOpenBrowser( QString address );

private:
  bool stripRedundantTweets();
  TwitterAPI::SocialNetwork network;
  QString login;
  StatusList *statusList;
  bool isVisible;
  int maxTweetCount;
  int scrollBarMargin;
  QModelIndex currentIndex;
  StatusListView *view;
};

#endif // TWEETMODEL_H
