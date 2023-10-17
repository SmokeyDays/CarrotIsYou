#include "CIYBoard.h"
#include "./lib/MiniMalloc.h"

bool CIYBoard::applyPush(const Vector &objs, int direction, int x, int y, Vector &pushList) {
  Vector objSolid = getObjectsByCondition([&](const CIYObject &obj) {
    return obj.x() == x && obj.y() == y && (nounHasAdj(obj.type(), STOP) || nounHasAdj(obj.type(), PULL));
  });
  
  if (objSolid.size()) {
    return false;
  }

  if(objs.size() == 0) {
    return true;
  }

  if(isAtEdge(x, y)) {
    return false;
  }

  int dx = DIRECTION[direction][0], dy = DIRECTION[direction][1];

  Vector nextObjs = getObjectsByCondition([&](const CIYObject &obj) {
    return obj.x() == x + dx && obj.y() == y + dy && nounHasAdj(obj.type(), PUSH);
  });

  if (!applyPush(nextObjs, direction, x + dx, y + dy, pushList)) {
    return false;
  }

  for (int i = 0; i < objs.size(); i++) {
    if (!pushList.has(objs[i])) {
      pushList.push(objs[i]);
    }
  }
  return true;
}

bool CIYBoard::applyPull(const Vector &objs, int direction, int x, int y, Vector &pullList) {

  auto [dx, dy] = DIRECTION[direction];

  for (int i = 0; i < objs.size(); i++) {
    for (auto existObj: pullList) {
      if(existObj != objs[i]) {
        pullList.push(objs[i]);
      }
    }
  }

  if (objs.size() > 0) {
    Vector nextObjs = getObjectsByPositionAndAdj(x - dx, y - dy, PULL);
    applyPull(nextObjs, direction, x - dx, y - dy, pullList);
  }
  return true;
}

void CIYBoard::insertRules(const Vector &subjects, const Vector &verbs, const Vector &objects) {
  for (auto subjectId : subjects) {
        for (auto objectId : objects) {
          for (auto verbId : verbs) {
            CIYType subjectType = getObject(subjectId).type();
            if(getGroupByType(subjectType) == NOUN_TEXT) {
              subjectType = (CIYType)(int(subjectType) - 40);
            }
            CIYType objectType = getObject(objectId).type();
            if(getGroupByType(objectType) == NOUN_TEXT) {
              objectType = (CIYType)(int(objectType) - 40);
            }
            CIYRule newRule(subjectType, getObject(verbId).type(), objectType);
            bool isConflict = false;
            if (rules.empty()) {
              rules.push(newRule);
            } else {
              bool isSame = false;
              for (auto &rule : rules) {
                if (rule.subject() == newRule.subject() && rule.verb() == newRule.verb() && rule.object() == newRule.object()) {
                  isSame = true;
                  break;
                }
              }
              if(!isSame) {
                for (auto &rule : rules) {
                  if (rule.subject() == newRule.subject() && rule.verb() == newRule.verb() && 
                    rule.object() == rule.subject() && rule.object() != newRule.object() && 
                    rule.verb() == IS && (getGroupByType(rule.object()) == NOUN || rule.object() == TEXT) && (getGroupByType(newRule.object()) == NOUN&& newRule.object() == TEXT)) {
                    isConflict = true;
                    break;
                  }
                }
                if(!isConflict) {
                  rules.push(newRule);
                }
              }
            }
            if (isConflict) {
              // TODO: Show Image of Conflict
            }
            
          }
        }
      }
}

void CIYBoard::checkRemove() {
  
  // Deal Defeat
  Vector objDefect = getObjectsByAdj(DEFEAT);
  for(int i = 0; i < objDefect.size(); i++) {
    Vector objYou = getObjectsByPositionAndAdj(getObject(objDefect[i]).x(), getObject(objDefect[i]).y(), YOU);
    if(objYou.size() > 0) {
      for(int j = 0; j < objYou.size(); j++) {
        if (atSameFloat(objDefect[i], objYou[j])) {
          removeObject(objYou[j]);
        }
      }
    }
  }

  // Deal Hot & Melt
  Vector objHot = getObjectsByAdj(HOT);
  for(int i = 0; i < objHot.size(); i++) {
    Vector objMelt = getObjectsByPositionAndAdj(getObject(objHot[i]).x(), getObject(objHot[i]).y(), MELT);
    if(objMelt.size() > 0) {
      for(int j = 0; j < objMelt.size(); j++) {
        if (atSameFloat(objHot[i], objMelt[j])) {
          removeObject(objMelt[j]);
        }
      }
    }
  }

  // Deal Shut & Open
  // TODO: Deal with Shut & Open which caused by Push
  Vector objShut = getObjectsByAdj(SHUT);
  for(int i = 0; i < objShut.size(); i++) {
    Vector objOpen = getObjectsByPositionAndAdj(getObject(objShut[i]).x(), getObject(objShut[i]).y(), OPEN);
    if(objOpen.size() > 0) {
      for(int j = 0; j < objOpen.size(); j++) {
        if (atSameFloat(objShut[i], objOpen[j])) {
          removeObject(objOpen[j]);
        }
      }
      removeObject(objShut[i]);
    }
  }

  // Deal Sink
  Vector objSink = getObjectsByAdj(SINK);
  for(int i = 0; i < objSink.size(); i++) {
    Vector objWillBeSink = getObjectsByPosition(getObject(objSink[i]).x(), getObject(objSink[i]).y());
    if(objWillBeSink.size() > 0) {
      for(int j = 0; j < objWillBeSink.size(); j++) {
        if (atSameFloat(objSink[i], objWillBeSink[j])) {
          removeObject(objWillBeSink[j]);
        }
      }
      removeObject(objSink[i]);
    }
  }

  // Deal Weak
  Vector objWeak = getObjectsByAdj(WEAK);
  for(int i = 0; i < objWeak.size(); i++) {
    Vector objOnWeak = getObjectsByPosition(getObject(objWeak[i]).x(), getObject(objWeak[i]).y());
    if(objOnWeak.size() > 0) {
      removeObject(objWeak[i]);
    }
  }
}

void CIYBoard::checkRules() {
  // check rules
  rules.clear();
  // check by row
  for(int i = 0; i < height; i++) {
    for(int j = 1; j < width - 1; j++) {
      // Filter Verbs That is "IS" or "HAS"
      Vector verbObjs = getObjectsByCondition([&](const CIYObject &obj) {
        return obj.x() == i && obj.y() == j && (obj.type() == IS || obj.type() == HAS);
      });
        
      if(verbObjs.size() == 0) {
        continue;
      }

      // Filter Subjects; Subjects are Nouns
      int last_subject = j - 1;
      Vector subjects = getObjectsByCondition([&](const CIYObject &obj) {
        return obj.x() == i && obj.y() == j - 1 && getGroupByType(obj.type()) == NOUN_TEXT;
      });

      if(subjects.size() == 0) {
        continue;
      }
      while(last_subject > 1) {
        Vector newSubjects = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == i && obj.y() == last_subject - 2 && getGroupByType(obj.type()) == NOUN_TEXT;
        });
        Vector andObjs = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == i && obj.y() == last_subject - 1 && obj.type() == AND;
        });
        if (newSubjects.size() == 0 || andObjs.size() == 0) {
          break;
        }
        last_subject -= 2;
        subjects.push(newSubjects);
      }

      // Filter Objects; Objects are Nouns or Adjectives
      int last_object = j + 1;
      Vector objects = getObjectsByCondition([&](const CIYObject &obj) {
        return obj.x() == i && obj.y() == j + 1 && (getGroupByType(obj.type()) == NOUN_TEXT || getGroupByType(obj.type()) == ADJ);
      });
      if(objects.size() == 0) {
        continue;
      }
      while(last_object < height - 2) {
        Vector newObjects = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == i && obj.y() == last_object + 2 && (getGroupByType(obj.type()) == NOUN_TEXT || getGroupByType(obj.type()) == ADJ);
        });
        Vector andObjs = getObjectsByPositionAndAdj(i, last_object + 1, AND);
        if (newObjects.size() == 0 || andObjs.size() == 0) {
          break;
        }
        last_object += 2;
        objects.push(newObjects);
      }

      insertRules(subjects, verbObjs, objects);     
    }
  }

  // check by column
  for(int i = 0; i < width; i++) {
    for(int j = 1; j < height - 1; j++) {
      // Filter Verbs That is "IS" or "HAS"
      Vector verbObjs = getObjectsByCondition([&](const CIYObject &obj) {
        return obj.x() == j && obj.y() == i && (obj.type() == IS || obj.type() == HAS);
      });
      if(verbObjs.size() == 0) {
        continue;
      }

      // Filter Subjects; Subjects are Nouns
      int last_subject = j - 1;
      Vector subjects = getObjectsByCondition([&](const CIYObject &obj) {
        return obj.x() == j - 1 && obj.y() == i && getGroupByType(obj.type()) == NOUN_TEXT;
      });
      if(subjects.size() == 0) {
        continue;
      }
      while(last_subject > 1) {
        Vector newSubjects = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == last_subject - 2 && obj.y() == i && getGroupByType(obj.type()) == NOUN_TEXT;
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
      Vector objects = getObjectsByCondition([&](const CIYObject &obj) {
        return obj.x() == j + 1 && obj.y() == i && (getGroupByType(obj.type()) == NOUN_TEXT || getGroupByType(obj.type()) == ADJ);
      });
      if(objects.size() == 0) {
        continue;
      }
      while(last_object < width - 2) {
        Vector newObjects = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == last_object + 2 && obj.y() == i && (getGroupByType(obj.type()) == NOUN_TEXT || getGroupByType(obj.type()) == ADJ);
        });
        Vector andObjs = getObjectsByPositionAndAdj(last_object + 1, i, AND);
        if (newObjects.size() == 0 || andObjs.size() == 0) {
          break;
        }
        last_object += 2;
        objects.push(newObjects);
      }

      insertRules(subjects, verbObjs, objects); 
    }
  }
}

void CIYBoard::move(int direction) {
    
  // move stage
  Vector objAutoMove = getObjectsByAdj(MOVE);
  Vector objMove[4];
  for(int i = 0; i < objAutoMove.size(); i++) {
    objMove[getObject(objAutoMove[i]).direction()].push(objAutoMove[i]);
  }

  Vector objYou = getObjectsByAdj(YOU);
  if (direction != -1) {
    objMove[direction].push(objYou);
  }

  for(int i = 0; i < 4; i++) {
    Vector shouldPush;
    if(objMove[i].size() > 0) {
      for(int j = 0; j < objMove[i].size(); ++j) {
        Vector single; single.push(objMove[i][j]);
        applyPush(single, i, getObject(objMove[i][j]).x(), getObject(objMove[i][j]).y(), shouldPush);
      }
    }
    for(int j = 0; j < shouldPush.size(); ++j) {
      getObject(shouldPush[j]).setX(getObject(shouldPush[j]).x() + DIRECTION[i][0]);
      getObject(shouldPush[j]).setY(getObject(shouldPush[j]).y() + DIRECTION[i][1]);
    }

    Vector shouldPull;
    if(shouldPush.size() > 0) {
      for(int j = 0; j < shouldPush.size(); ++j) {
        Vector single; single.push(shouldPush[j]);
        applyPull(single, i, getObject(shouldPush[j]).x(), getObject(shouldPush[j]).y(), shouldPull);
      }
    } 
    for(int j = 0; j < shouldPull.size(); ++j) {
      getObject(shouldPull[j]).setX(getObject(shouldPull[j]).x() - DIRECTION[i][0]);
      getObject(shouldPull[j]).setY(getObject(shouldPull[j]).y() - DIRECTION[i][1]);
    }
  }

  checkRules();

  checkRemove();

  // Deal Tele
  Vector objTele = getObjectsByAdj(TELE);
  if (objTele.size() > 1) {
    for(int i = 0; i < objTele.size(); i++) {
      int j = (i + 1) % objTele.size();
      Vector objToTele = getObjectsByPosition(getObject(objTele[i]).x(), getObject(objTele[i]).y());
      for(int k = 0; k < objToTele.size(); k++) {
        if (atSameFloat(objTele[i], objToTele[k])) {
          getObject(objToTele[k]).setX(getObject(objTele[j]).x());
          getObject(objToTele[k]).setY(getObject(objTele[j]).y());
        }
      }
    }
  }

  checkRemove();

  // Deal Win
  Vector objWin = getObjectsByAdj(WIN);
  objYou = getObjectsByAdj(YOU);
  for(int i = 0; i < objWin.size(); ++i) {
    for(int j = 0; j < objYou.size(); ++j) {
      if (atSameFloat(objWin[i], objYou[j])) {
        isWin = true;
        return;
      }
    }
  }
}
