C++ OOP (object_oriented) tutorial with project
==============

## How to use ##

1. read slides (Slide folder) and watch the tutorial (learn2implement)
2. read project structure
3. start implement project by your self
4. ask a question in issue
5. add an extra feature to project like a new agent and new structure
6. fork the project and create a folder by your id in /student_result
7. send pull request
8. :)

![cover](https://github.com/maze1377/CPP-object_oriented-tutorial-with-project/blob/master/ScreenShot/cover.jpg)

## Purpose ##

• Working with a set of classes that have clearly defined roles and responsibilities, such as a simple form of the Model-ViewController pattern.

• Working with a class hierarchy in which inheritance helps re-use code.

• Using virtual functions to achieve polymorphic behavior.

• Observing the order of construction and destruction in a class hierarchy.

• Using abstract base classes to specify the interface to derived classes.

• Using a "fat interface" to control derived class objects polymorphically.

• Using separate containers of derived-class pointers to distinguish object types.

• Calling base class functions from derived class functions to re-use code within the class hierarchy.

• Using mixin multiple inheritances to take advantage of a pre-existing base class.

• Using private inheritance to demonstrate re-use of implementation rather than an interface.

• Making header files as simple as possible to avoid unnecessary coupling.

• Using a simple form of Factory to further reduce coupling.


Also, you will practice some additional programming techniques:

• Working with objects that have state and state changes.

• Using exceptions for user input errors to simplify the program structure, using std::exception as a base exception class.

• Further use of the Standard Library to simplify coding.

Finally, certain aspects of the coding may be new to you, although they are ancient and traditional issues:

• Using floating point numbers and dealing with some of the representational issues. For example, comparisons for equality are
usually unreliable.

• Using a 3-dimensional array-type data structure.

# The author advises you

• before reading the answer to it by yourself

• search in google for example for the part of you don't know and try to learn by example

• for check your answer add a new feature to project and see Add features by adding code, not by changing code is possible or not

• share your answer by other people and ask them to help you

### the command you have to support is :

| Command | Description |
| --- | --- |
| [agent_name] move X Y | set moving  distention point  |
| [agent_name] attack [agent_name2] | first agent attack second agent if it's possible |
| [agent_name] stop | stop moving to distention point   |
| [agent_name] work [structure_source] [structure_destination] | agent start working in that place  |
| train [agent_name] [agent_type] X Y | create new Soldier or Peasant at point |
| build  [structure_name] [structure_type] X Y | create new Farm  or Town_Hall at point |
| go | go to the target(x,y) that is set by (move X Y) or update |
| status | show status of all object in the map |
| open map |  ready to show all map by show command  |
| open [agent_name] | ready to show console map around the agent by show command |
| open [structure_name] | ready to show console map around the structure by show command |
| open health | show health of every agent by show command |
| close [agent_name] | remove console map around the agent when  show command enter |
| close [structure_name] | remove console map around the structure when show command enter |
| close map | remove console map  when  show command enter |
| close health | remove health of every agent when  show command enter |
| zoom [1 - 10] | map zoom setting |
| pan  X Y | set map start point  |
| size  X | set map start point  |
| show | show all open object |
| default | back to default settings |
| quit | exit the game |

# game simulation out Put sample

```cmd
  38 . . . . . . . . . . . . . . . Ir. . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
  32 . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . Su. . . . . . . . . . . . . . Pa. . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
  26 . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . Me. . . . . . . Zu. . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
  20 . . . . . . . . . . . . Bu. . Sh. . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
  14 . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . Pi. . Ri. . . . . . . . . . . . . .
   8 . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
   2 . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
  -4 . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
     . . . . . . . . . . . . . . . . . . . . . . . . .
 -10 . . . . . . . . . . . . . . . . . . . . . . . . .
   -10    -4     2     8    14    20    26    32    38
```
# contributors
| id_github | work |
| --- | --- |
|fbghkh1999|added new Agent (Archer) to project |
|Sina Aminian|change readme|

# last word

The project description is not for me, someone asked me to implement it for her, when I saw it is well in terms of education, I decided to build this git repository :)
