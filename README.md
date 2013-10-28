This program is World of Tanks crew experience calculator.
It will calculate required experience for specific master/skill/perk level to another.

Usage: 

    $./wotexp [skill class] [skill level] [[experience] | [target skill class] [target skill level]]

    Skill class:
    0 means tank mastery.
    1 and above means skill/perk number.

    Skill level:
    % of skill class progress.

Example:

    If I want to know the experience need to have my crew tank mastery from 91% to 100%.
    $./wotexp 0 91 0 100

    Program result:

    Current exp 69,078
    To Master 100%, you need 36,002 exp.
    ============
    Retrain master, same class
    Paid: 
    From Major class 100
    To   Major class  90, Exp lost = 39,157, Residual Exp = 0
    To next level, you need 3,155 exp.
    Retrain master, different class
    Paid: 
    From Major class 100
    To   Major class  80, Exp lost = 63,866, Residual Exp = 0
    To next level, you need 1,991 exp.


If the target skill class and level are not provided.
The program will show you the retrain result.

    If I want to know paid retrain result of my 53% 3 skill crew.
    $./wotexp 3 53

    Program result:

    Current exp 719,270
    To next level, you need 4,593 exp.
    ============
    Retrain Skill/Perk:
    Paid: 
    From Perk/Skill 3,  53%
    To   Perk/Skill 3,  23%, Exp lost = 71,927, Residual Exp = 1,057
    To next level, you need 97 exp.

You can also calculate the expected level with specific amount of exp.

    If I want to know with 10,000 exp will up level your crew to which level.
    $./wotexp 1 10 10000

    Program result:

    Current exp 1,245.
    With 10,000 exp, you can upgrade to 1,  39%, 563 exp left.
    To next level, you need 40 exp.



Known issue:

    All mathmetic calculation for each skill level isn't identical to in game setting.
    There will be error accumulated to higher skill class
