#include "CIYBoard.h"

bool CIYBoard::applyMove(const Vector &objs, int direction, int x, int y) {
  bool posStop = false;
  for (int i = 1; i < objs.size(); i++) {
    posStop |= hasAdj(objs[i], STOP);
  }

  if (posStop || isAtEdge(x, y)) {
    return false;
  }

  auto [dx, dy] = DIRECTION[direction];

  Vector nextObjs = getObjectsByPositionAndAdj(x + dx, y + dy, PUSH);
  if (nextObjs.size() > 0 && !applyMove(nextObjs, direction, x + dx, y + dy)) {
    return false;
  }
  for (int i = 0; i < objs.size(); i++) {
    getObject(objs[i]).x += dx;
    getObject(objs[i]).y += dy;
  }
  return true;
}

void CIYBoard::move(int direction) {
  // move stage
  Vector objAutoMove = getObjectsByAdj(MOVE);
  Vector objMove[4];
  for(int i = 0; i < objAutoMove.size(); i++) {
    objMove[getObject(objAutoMove[i]).direction].push(objAutoMove[i]);
  }

  Vector objYou = getObjectsByAdj(YOU);
  objMove[direction].push(objYou);

  for(int i = 0; i < 4; i++) {
    if(objMove[i].size() > 0) {
      applyMove(objMove[i], i, getObject(objMove[i][0]).x, getObject(objMove[i][0]).y);
    }
  }

  // check rules
  ruleNum = 0;
  // check by row
  for(int i = 0; i < height; i++) {
    Vector objs = getObjectsByPosition(0, i);
    for(int j = 1; j < width - 1; j++) {
      // Filter Verbs That is "IS" or "HAS"
      Vector verbObjs = getObjectsByPositionAndAdj(j, i, IS);
      verbObjs.push(getObjectsByPositionAndAdj(j, i, HAS));
      if(verbObjs.size() == 0) {
        continue;
      }

      // Filter Subjects; Subjects are Nouns
      int last_subject = j - 1;
      Vector subjects = getObjectsByCondition([&](CIYObject obj) {
        return obj.x == j - 1 && obj.y == i && getGroupByType(obj.type) == NOUN_TEXT;
      });
      if(subjects.size() == 0) {
        continue;
      }
      while(last_subject > 1) {
        Vector newSubjects = getObjectsByCondition([&](CIYObject obj) {
          return obj.x == last_subject - 2 && obj.y == i && getGroupByType(obj.type) == NOUN_TEXT;
        });
        Vector andObjs = getObjectsByPositionAndAdj(last_subject - 1, i, AND);
        if (newSubjects.size() == 0 || andObjs.size() == 0) {
          break;
        }
        last_subject -= 2;
        subjects.push(newSubjects);
      }

      // Filter Objects; Objects are Nouns or Adjectives
      int last_object = j + 1;
      Vector objects = getObjectsByCondition([&](CIYObject obj) {
        return obj.x == j + 1 && obj.y == i && (getGroupByType(obj.type) == NOUN_TEXT || getGroupByType(obj.type) == ADJ);
      });
      if(objects.size() == 0) {
        continue;
      }
      while(last_object < width - 2) {
        Vector newObjects = getObjectsByCondition([&](CIYObject obj) {
          return obj.x == last_object + 2 && obj.y == i && (getGroupByType(obj.type) == NOUN_TEXT || getGroupByType(obj.type) == ADJ);
        });
        Vector andObjs = getObjectsByPositionAndAdj(last_object + 1, i, AND);
        if (newObjects.size() == 0 || andObjs.size() == 0) {
          break;
        }
        last_object += 2;
        objects.push(newObjects);
      }
      for(int k = 0; k < subjects.size(); k++) {
        for(int l = 0; l < objects.size(); l++) {
          for(int m = 0; m < verbObjs.size(); m++) {
            CIYRule rule = {getObject(subjects[k]).type, getObject(verbObjs[m]).type, getObject(objects[l]).type};
            if(ruleNum == 0) {
              rules[ruleNum++] = rule;
            } else {
              bool isSame = false;
              for(int n = 0; n < ruleNum; n++) {
                if(rules[n].noun == rule.noun && rules[n].verb == rule.verb && rules[n].adj == rule.adj) {
                  isSame = true;
                  break;
                }
              }
              if(!isSame) {
                bool isConflict = false;
                for(int n = 0; n < ruleNum; n++) {
                  if(rules[n].noun == rule.noun && rules[n].verb == rule.verb && rules[n].adj != rule.adj && rule.verb == IS) {
                    isConflict = true;
                    break;
                  }
                }
                if(!isConflict) {
                  rules[ruleNum++] = rule;
                }
              }
            }
            ruleNum++;
          }
        }
      }
    }
  }
}
