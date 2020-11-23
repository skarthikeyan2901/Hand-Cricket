# Hand-Cricket
 A basic hand cricket game in C<br><br>
 Data Structures used : Stack as a Linked List<br><br>
 
 Hand cricket is a game in which any number of players can play a game
of cricket using their hands (in this case machines) against each other.<br><br>
 It is like any typical hand cricket game where a batsman and a bowler
put a number and if the numbers are the same the batsman is out. If not
the batsman keeps adding his score.<br><br>
 In real life, the batsman and the bowler put the number simultaneously
but here we cannot do that. So we hid or masked the input of the bowler
and the batsman to prevent cheating.<br><br>
 This game not only allows one-on-one matches but also team matches
where a team can have multiple players. All the players can input their
names which we store in an array of structures. In the program, we use
it as a pointer to the array of structures.<br><br>
 We also have a feature which allows the teams to have a toss to
choose for batting or bowling which we coded using random.<br><br>
 We also have a feature where the batting team can decide the team’s
batting order by inputting the order as numbers.<br><br>
 The players are then pushed into a stack according to the batting order
in reverse order so that the opener is in the top of the stack and
whenever the batsman gets out his record is popped.<br><br>
 We also have a well-formatted score board that displays the individual
scores of each player from both teams.<br><br>
