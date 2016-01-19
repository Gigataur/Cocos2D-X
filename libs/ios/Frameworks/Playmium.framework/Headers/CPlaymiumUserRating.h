//
//  CPlaymiumUserRating.h
//  PlaymiumFramework
//
//  Copyright © 2015 Gigataur. All rights reserved.
//

#ifndef CPlaymiumUserRating_h
#define CPlaymiumUserRating_h


class CPlaymiumUserRating
{
public:
  /**
   Decides whether or not to display a Please-Rate-This-Game prompt to the user, and if so opens the prompt.
   Some reasons to not open the prompt include: the user has already rated the game, the user has previously declined to rate
   the game, etc.
   Note that this method will return immediately whether or not the prompt is opened.
   @return true if the prompt is opened, false if not.
   */
  static bool showOptionalUserRatingDlg();
  
  /**
   Opens a Please-Rate-This-Game prompt to the user.
   Note that this method will return immediately whether or not the prompt is opened.
   */
  static void showUserRatingDlg();
  
  /**
   Similar to the user rating above, if the ratngs should be opened it will return true and invoke the shouldShowRatings callback.
   */
  static bool checkForUserRating();
  
  // asks for feedback if they accept it will launch feedback task
  static void askForFeedback();
  
  // forces the screen to launch to showing the rating screen for the app
  static void launchRatings();
  
  // function called when you need to delay showing the ratings
  static void showRatingsLater();
};

#endif /* CPlaymiumUserRating_h */
