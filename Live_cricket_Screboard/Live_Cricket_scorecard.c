#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYERS 11

typedef struct {
    char name[50];
    int runs;
    int balls_faced;
    int fours;
    int sixes;
} Player;

typedef struct {
    char name[50];
    int overs_bowled;
    int runs_conceded;
    int wickets_taken;
} Bowler;

void first_inning(Player batsmen[], Bowler bowlers[]);
int second_inning(Player batting_players[], Player bowling_players[], Bowler bowlers[], int overs);
void display_batting_card(Player players[]);
void display_bowling_stats(Bowler bowlers[]);
void display_scorecard(Player batting_players[], Player bowling_players[], Bowler bowlers[], char team[50], int total_score, int total_wickets);

char Team1[50];
char Team2[50];
int toss, target, overs, score, wickets, inning = 1;
float runrate;
int balls, p_balls;
int current_outs = 0;
float c_overs;
int bat_first;
Player batting_players[MAX_PLAYERS];
Player bowling_players[MAX_PLAYERS];
Bowler bowlers[MAX_PLAYERS];

int main() {
    printf("-------------------------------------------\n");
    printf("\t\tBeast Cricket Scorer\n");
    printf("-------------------------------------------\n");
    printf("Press any key to Continue\n");
    getch();
    system("cls");

    printf("Enter Name of Team1: ");
    scanf("%s", Team1);
    printf("Enter Name of Team2: ");
    scanf("%s", Team2);
    printf("Enter the number of overs: ");
    scanf("%d", &overs);
    balls = overs * 6;

    printf("Which Team is batting first?\n");
    printf("[1] %s\n[2] %s\n", Team1, Team2);
    scanf("%d", &toss);
    while (toss != 1 && toss != 2) {
        printf("Enter a valid choice!\n");
        printf("Which Team is batting first?\n");
        printf("[1] %s\n[2] %s\n", Team1, Team2);
        scanf("%d", &toss);
    }

    if (toss == 1) {
        printf("%s is batting first\n", Team1);
        first_inning(batting_players, bowlers);
        bat_first = 1;
    } else {
        printf("%s is batting first\n", Team2);
        first_inning(batting_players, bowlers);
        bat_first = 2;
    }
    getch();
    system("cls");

    if (target > 0) {
        if (bat_first == 1) {
            second_inning(batting_players, bowling_players, bowlers, overs);
        } else {
            second_inning(bowling_players, batting_players, bowlers, overs);
        }
    }

    return 0;
}


 void first_inning(Player batsmen[], Bowler bowlers[]) {
  p_balls = 0;
  score = 0;
  wickets = 0;
  int j, scorer, r, extras = 0;
  int current_batsmen[2] = {0, 1}; // Indices of first two batsmen
  int current_bowler_index = 0;
  printf(":--------------First Innings----------------\n");

  // Input names of first two batsmen
  for (int i = 0; i < 2; i++) {
    printf("Enter Name of Batsman %d: ", i+1);
    scanf("%s", batsmen[i].name);
    batsmen[i].runs = 0;
    batsmen[i].balls_faced = 0;
  }

  for (j = 0; j < balls; j++) {
   if (p_balls % 6 == 0) {
  // Update bowler index first
  current_bowler_index = (current_bowler_index + overs - 1) % overs;
  printf("Enter Name of Bowler: ");
  scanf("%s", bowlers[current_bowler_index].name);
      bowlers[current_bowler_index].overs_bowled = 1;
    bowlers[current_bowler_index].runs_conceded = 0;
      bowlers[current_bowler_index].wickets_taken = 0;

    }

    while (1) {
      printf("Last ball...\n");
      printf("[1]Normal delivery\n[2]No ball/wide\n");
      scanf("%d", &scorer);
      if (scorer == 1 || scorer == 2) {
        break;
      } else {
        printf("Enter a valid choice!\n");
      }
    }

    printf("\nRuns on last ball\n");
    printf("[0]Dot ball\n[1]1 run\n[2]2 runs\n[3]3 runs\n[4]4 \n[5]6\n[6]Wicket!\n[7]Wide\n[8]No ball\n[9]Bye\n");
    scanf("%d", &r);
    if (r < 0 || r > 9) {
      printf("Enter a valid choice!\n");
      j--;
      continue;
    }

    if (scorer == 1) {
      p_balls++;
      if (p_balls % 6 == 0) {
        c_overs += 0.5;
        // Change batsman after every over or after scoring 1 or 3 runs
        if (batsmen[current_batsmen[0]].runs == 1 || batsmen[current_batsmen[0]].runs == 3 || p_balls % 6 == 0) {
          // Switch to the other batsman for next ball
          current_batsmen[0] = (current_batsmen[0] + 1) % 2;
        }
      } else {
        c_overs += 0.1;
      }
    } else if (scorer == 2) {
      score += 1;
      extras += 1;
    }

    switch (r) {
      case 0:
        batsmen[current_batsmen[0]].balls_faced++;
        break;
      case 1:
        score += 1;
        batsmen[current_batsmen[0]].runs += 1;
        batsmen[current_batsmen[0]].balls_faced++;
         current_batsmen[0] = (current_batsmen[0] + 1) % 2;
        break;
      case 2:
        score += 2;
        batsmen[current_batsmen[0]].runs += 2;
        batsmen[current_batsmen[0]].balls_faced++;
        break;
      case 3:
        score += 3;
        batsmen[current_batsmen[0]].runs += 3;
        batsmen[current_batsmen[0]].balls_faced++;
        // Switch to the other batsman for next ball after 3 runs
        current_batsmen[0] = (current_batsmen[0] + 1) % 2;
        break;

        case 4:
                score += 4;
                batsmen[current_batsmen[0]].runs += 4;
                batsmen[current_batsmen[0]].balls_faced++;
                break;
            case 5:
                score += 6;
                batsmen[current_batsmen[0]].runs += 6;
                batsmen[current_batsmen[0]].balls_faced++;
                break;
            case 6:
                wickets++;
                batting_players[current_batsmen[0]].balls_faced++;
        // Find the index of the next batsman (considering all batsmen)
                int next_batsman = (current_batsmen[0] + 1) % 11;
        // Check if all batsmen are out
                if (wickets < 10) {
                printf("Enter Name of Batsman %d: ", wickets + 1);
                scanf("%s", batting_players[next_batsman].name);
                batting_players[next_batsman].runs = 0;
                batting_players[next_batsman].balls_faced = 0;
             }
                break;

            case 7:
                score += 1;
                extras += 1;
                break;
            case 8:
                score += 1;
                extras += 1;
                break;
            case 9:
                extras += 1;
                break;
            default:
                break;
        }

        bowlers[current_bowler_index].runs_conceded += r;
  if (r == 6) {
    bowlers[current_bowler_index].wickets_taken++;
  }
  runrate = score / c_overs;
  printf(":--------------First Innings----------------\n");
  printf("Inning 1|");
  printf("\nSCORE---%s|%d-%d-%d|\t\t |overs:- %.1f|", Team1, score, wickets, extras, c_overs);
  printf("\n RR:-%.2f", runrate);

  // Update details of the current batsman (the one who DIDN'T get out)
  int not_out_batsman = (current_batsmen[0] + 1) % 2;
  printf("\n Batsman 1: %s - %d (%d)\n", batting_players[current_batsmen[0]].name, batting_players[current_batsmen[0]].runs, batting_players[current_batsmen[0]].balls_faced);
  printf(" Batsman 2: %s - %d (%d)\n", batting_players[not_out_batsman].name, batting_players[not_out_batsman].runs, batting_players[not_out_batsman].balls_faced);

  printf("\n Bowler: %s | Runs Conceded: %d | Wickets Taken: %d\n", bowlers[current_bowler_index].name, bowlers[current_bowler_index].runs_conceded, bowlers[current_bowler_index].wickets_taken);
  getch();
  system("cls");

  if (wickets == 10 || p_balls == balls) {
    inning = 2;
    if (inning == 2) {
      target = score + 1;
      printf("Target is %d\n", target);
    }
    break;
  }
}
 }


int second_inning(Player batting_players[], Player bowling_players[], Bowler bowlers[], int overs) {
  p_balls = 0;
  c_overs = 0;
  score = 0;
  wickets = 0;
  int j, scorer, r, extras = 0;
  int current_batsmen[2] = {0, 1}; // Indices of first two batsmen
  int current_bowler_index = 0;
  printf(":--------------SECOND Innings----------------\n");

  // Input names of first two batsmen
  for (int i = 0; i < 2; i++) {
    printf("Enter Name of Batsman %d: ", i+1);
    scanf("%s", batting_players[i].name);
    batting_players[i].runs = 0;
    batting_players[i].balls_faced = 0;
  }

  for (j = 0; j < balls; j++) {
    if (p_balls % 6 == 0) {
      printf("Enter Name of Bowler: ");
      scanf("%s", bowlers[current_bowler_index].name);
      bowlers[current_bowler_index].overs_bowled = 1;
      bowlers[current_bowler_index].runs_conceded = 0;
      bowlers[current_bowler_index].wickets_taken = 0;
      current_bowler_index = (current_bowler_index + 1) % overs;
    }

    while (1) {
      printf("Last ball...\n");
      printf("[1]Normal delivery\n[2]No ball/wide\n");
      scanf("%d", &scorer);
      if (scorer == 1 || scorer == 2) {
        break;
      } else {
        printf("Enter a valid choice!\n");
      }
    }

    printf("\nRuns on last ball\n");
    printf("[0]Dot ball\n[1]1 run\n[2]2 runs\n[3]3 runs\n[4]4 \n[5]6\n[6]Wicket!\n[7]Wide\n[8]No ball\n[9]Bye\n");
    scanf("%d", &r);
    if (r < 0 || r > 9) {
      printf("Enter a valid choice!\n");
      j--;
      continue;
    }

    if (scorer == 1) {
      p_balls++;
      if (p_balls % 6 == 0) {
        c_overs += 0.5;
        // Change batsman after every over or after scoring 1 or 3 runs
        if (batting_players[current_batsmen[0]].runs == 1 || batting_players[current_batsmen[0]].runs == 3 || p_balls % 6 == 0) {
          // Switch to the other batsman for next ball
          current_batsmen[0] = (current_batsmen[0] + 1) % 2;
        }
      } else {
        c_overs += 0.1;
      }
    } else if (scorer == 2) {
      score += 1;
      extras += 1;
    }

    switch (r) {
      case 0:
        batting_players[current_batsmen[0]].balls_faced++;
        break;
      case 1:
        score += 1;
        batting_players[current_batsmen[0]].runs += 1;
        batting_players[current_batsmen[0]].balls_faced++;
        current_batsmen[0] = (current_batsmen[0] + 1) % 2;
        break;
      case 2:
        score += 2;
        batting_players[current_batsmen[0]].runs += 2;
        batting_players[current_batsmen[0]].balls_faced++;
        break;
      case 3:
        score += 3;
        batting_players[current_batsmen[0]].runs += 3;
        batting_players[current_batsmen[0]].balls_faced++;
        // Switch to the other batsman for next ball after 3 runs
        current_batsmen[0] = (current_batsmen[0] + 1) %2;

            case 4:
                score += 4;
                batting_players[current_batsmen[0]].runs += 4;
                batting_players[current_batsmen[0]].balls_faced++;
                break;
            case 5:
                score += 6;
                batting_players[current_batsmen[0]].runs += 6;
                batting_players[current_batsmen[0]].balls_faced++;
                break;
            case 6:
                wickets++;
               batting_players[current_batsmen[0]].balls_faced++;

              // Find the index of the next batsman (considering all batsmen)
               int next_batsman = (current_batsmen[0] + 1) % 11;

              // Check if all batsmen are out
              if (wickets < 10) {
                printf("Enter Name of Batsman %d: ", wickets+1);
                scanf("%s", batting_players[next_batsman].name);
                batting_players[next_batsman].runs = 0;
                 batting_players[next_batsman].balls_faced = 0;
    }

             break;
           case 7:
        score += 1;
        extras += 1;
    break;
           case 8:
         score += 1;
          extras += 1;
     break;
             case 9:
              extras += 1;
    break;
  default:
    break;
}

bowlers[current_bowler_index].runs_conceded += r;
if (r == 6) {
  bowlers[current_bowler_index].wickets_taken++;
}
runrate = score / c_overs;
printf(":--------------Second Innings----------------\n");
printf("Inning 2|");
printf("\nSCORE---%s|%d-%d-%d|\t\t |overs:- %.1f|", Team2, score, wickets, extras, c_overs);
printf("\n RR:-%.2f", score / c_overs);

// Update details of the current batsman (the one who DIDN'T get out)
int not_out_batsman = (current_batsmen[0] + 1) % 11;
printf("\n Batsman 1: %s - %d (%d)\n", batting_players[current_batsmen[0]].name, batting_players[current_batsmen[0]].runs, batting_players[current_batsmen[0]].balls_faced);
printf(" Batsman 2: %s - %d (%d)\n", batting_players[not_out_batsman].name, batting_players[not_out_batsman].runs, batting_players[not_out_batsman].balls_faced);
printf("\n Bowler: %s | Runs Conceded: %d | Wickets Taken: %d\n", bowlers[current_bowler_index].name, bowlers[current_bowler_index].runs_conceded, bowlers[current_bowler_index].wickets_taken);
getch();
system("cls");

if (wickets == 10 || p_balls == balls || score >= target) {
  if (score >= target) {
    printf("%s Won the Match!\n", Team2);
  } else {
    printf("%s Won the Match!\n", Team1);
  }
  return 0;
}
  }
}


