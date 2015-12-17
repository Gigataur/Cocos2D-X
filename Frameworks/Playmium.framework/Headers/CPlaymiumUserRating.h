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
};

#endif /* CPlaymiumUserRating_h */
