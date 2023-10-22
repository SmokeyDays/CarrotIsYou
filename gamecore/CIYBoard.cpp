#include "CIYBoard.h"
#include "./lib/MiniMalloc.h"

void CIYBoard::removeObject(int obj) {
  Vector rulesHAS = getRulesByCondition([&](const CIYRule &rule) {
    return rule.subject() == objects[obj].type() && rule.verb() == HAS && getGroupByType(rule.object()) == NOUN;
  });
  for(int i = 0; i < rulesHAS.size(); ++i) {
    CIYObject newObj = CIYObject(objects[obj].x(), objects[obj].y(), objects[obj].direction(), rules[rulesHAS[i]].object());
    newObjects.push(newObj);
  }
  objects[obj].setType(EMPTY);
}

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

  int dx = DIRECTION[direction][0], dy = DIRECTION[direction][1];

  if(isOutEdge(x + dx, y + dy)) {
    return false;
  }

  Vector nextObjs = getObjectsByCondition([&](const CIYObject &obj) {
    return obj.x() == x + dx && obj.y() == y + dy && (nounHasAdj(obj.type(), PUSH) || (isText(obj.type())));
  });

  Vector objShut = getObjectsByCondition([&](const CIYObject &obj) {
    return obj.x() == x + dx && obj.y() == y + dy && nounHasAdj(obj.type(), SHUT);
  });
  for (int i = 0; i < objs.size(); ++i) {
    if (objHasAdj(objs[i], OPEN)) {
      bool usedOpen = 0;
      for (int j = 0; j < objShut.size(); ++j) {
        if (atSameFloat(objs[i], objShut[j])) {
          usedOpen = 1;
          removeObject(objShut[j]);
        }
      }
      if(usedOpen) {
        removeObject(objs[i]);
      }
    }
  }
  Vector objWeak = getObjectsByCondition([&](const CIYObject &obj) {
    return obj.x() == x + dx && obj.y() == y + dy && nounHasAdj(obj.type(), WEAK);
  });
  for (int i = 0; i < objWeak.size(); ++i) {
    removeObject(objWeak[i]);
  }

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

  int dx = DIRECTION[direction][0], dy = DIRECTION[direction][1];

  if(isOutEdge(x - dx, y - dy)) {
    return false;
  }
  Vector nextObjs = getObjectsByPositionAndAdj(x - dx, y - dy, PULL);
  if (nextObjs.size() > 0) {
    for (int i = 0; i < nextObjs.size(); i++) {
      if(!pullList.has(nextObjs[i])) {
        pullList.push(nextObjs[i]);
      }
    }
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
        if (rules.empty()) {
          rules.push(newRule);
          objectRelRules.push(rules.size() - 1);
          objectRelRules.push(rules.size() - 1);
          objectRelRules.push(rules.size() - 1);
          ruleRelObjects.push(subjectId);
          ruleRelObjects.push(objectId);
          ruleRelObjects.push(verbId);
        } else {
          int same = -1;
          for (int i = 0; i < rules.size(); ++i) {
            CIYRule &rule = rules[i];
            if (rule.subject() == newRule.subject() && rule.verb() == newRule.verb() && rule.object() == newRule.object()) {
              same = i;
              break;
            }
          }
          if (same >= 0) {
            objectRelRules.push(same);
            objectRelRules.push(same);
            objectRelRules.push(same);
            ruleRelObjects.push(subjectId);
            ruleRelObjects.push(objectId);
            ruleRelObjects.push(verbId);
          } else {
            rules.push(newRule);
            objectRelRules.push(rules.size() - 1);
            objectRelRules.push(rules.size() - 1);
            objectRelRules.push(rules.size() - 1);
            ruleRelObjects.push(subjectId);
            ruleRelObjects.push(objectId);
            ruleRelObjects.push(verbId);
          }
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
      bool usedShut = 0;
      for(int j = 0; j < objOpen.size(); j++) {
        if (atSameFloat(objShut[i], objOpen[j])) {
          usedShut = 1;
          removeObject(objOpen[j]);
        }
      }
      if(usedShut) {
        removeObject(objShut[i]);
      }
    }
  }

  // Deal Sink
  Vector objSink = getObjectsByAdj(SINK);
  for(int i = 0; i < objSink.size(); i++) {
    Vector objWillBeSink = getObjectsByPosition(getObject(objSink[i]).x(), getObject(objSink[i]).y());
    if(objWillBeSink.size() > 0) {
      bool usedSink = 0;
      for(int j = 0; j < objWillBeSink.size(); j++) {
        if (objSink[i] != objWillBeSink[j] && atSameFloat(objSink[i], objWillBeSink[j])) {
          usedSink = 1;
          removeObject(objWillBeSink[j]);
        }
      }
      if (usedSink) {
        removeObject(objSink[i]);
      }
    }
  }

  // Deal Weak
  Vector objWeak = getObjectsByAdj(WEAK);
  for(int i = 0; i < objWeak.size(); i++) {
    Vector objOnWeak = getObjectsByPosition(getObject(objWeak[i]).x(), getObject(objWeak[i]).y());
    if(objOnWeak.size() > 0) {
      for(int j = 0; j < objOnWeak.size(); j++) {
        if(objWeak[i] != objOnWeak[j]) {
          removeObject(objWeak[i]);
          break;
        }
      }
    }
  }
}

void CIYBoard::checkRules() {
  // check rules
  rules.clear();
  illegalObjects.clear();
  objectRelRules.clear();
  ruleRelObjects.clear();
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
      while(last_object < width - 2) {
        Vector newObjects = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == i && obj.y() == last_object + 2 && (getGroupByType(obj.type()) == NOUN_TEXT || getGroupByType(obj.type()) == ADJ);
        });
        Vector andObjs = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == i && obj.y() == last_object + 1 && obj.type() == AND;
        });
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
        Vector andObjs = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == last_subject - 1 && obj.y() == i && obj.type() == AND;
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
        return obj.x() == j + 1 && obj.y() == i && (getGroupByType(obj.type()) == NOUN_TEXT || getGroupByType(obj.type()) == ADJ);
      });
      if(objects.size() == 0) {
        continue;
      }
      while(last_object < height - 2) {
        Vector newObjects = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == last_object + 2 && obj.y() == i && (getGroupByType(obj.type()) == NOUN_TEXT || getGroupByType(obj.type()) == ADJ);
        });
        Vector andObjs = getObjectsByCondition([&](const CIYObject &obj) {
          return obj.x() == last_object + 1 && obj.y() == i && obj.type() == AND;
        });
        if (newObjects.size() == 0 || andObjs.size() == 0) {
          break;
        }
        last_object += 2;
        objects.push(newObjects);
      }

      insertRules(subjects, verbObjs, objects); 
    }
  }

  // resolve conflict 
  for(int i = 0; i < rules.size(); ++i) {
    if(rules[i].object() == rules[i].subject() && rules[i].verb() == IS) {
      for(int j = 0; j < rules.size(); ++j) {
        if(i != j && rules[i].subject() == rules[j].subject() && rules[j].verb() == IS && getGroupByType(rules[j].object()) == NOUN) {
          rules[j] = CIYRule(EMPTY, IS, EMPTY);
          for(int k = 0; k < objectRelRules.size(); ++k) {
            if(objectRelRules[k] == j) {
              illegalObjects.push(getObject(ruleRelObjects[k]));
            }
          }
        }
      }
    }
  }

  // puts("Rules:");
  // for(int i = 0; i < rules.size(); ++i) {
  //   printf("%d %d %d\n", rules[i].subject(), rules[i].verb(), rules[i].object());
  // }
}

void CIYBoard::clearEmpty() {
  for(int i = 0; i < objects.size(); ++i) {
    if(objects[i].type() == EMPTY) {
      objects[i] = objects[objects.size() - 1];
      objects.pop();
    }
  }
  newObjects.clear();
}

void CIYBoard::move(int direction) {
  
  clearEmpty();
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
  isDefeat = (!objYou.size());
  for(int i = 0; i < 4; i++) {
    if(objMove[i].size()) {
      isDefeat = false;
    }
  }
  for(int i = 0; i < 4; i++) {
    Vector shouldPush;
    if(objMove[i].size() > 0) {
      for(int j = 0; j < objMove[i].size(); ++j) {
        Vector single; single.push(objMove[i][j]);
        bool moveable = applyPush(single, i, getObject(objMove[i][j]).x(), getObject(objMove[i][j]).y(), shouldPush);
        if(!moveable) {
          getObject(objMove[i][j]).setDirection((i + 2) % 4);
        }
      }
    }

    Vector shouldPull;
    if(shouldPush.size() > 0) {
      for(int j = 0; j < shouldPush.size(); ++j) {
        Vector single; single.push(shouldPush[j]);
        applyPull(single, i, getObject(shouldPush[j]).x(), getObject(shouldPush[j]).y(), shouldPull);
      }
    } 
    
    for(int j = 0; j < shouldPush.size(); ++j) {
      getObject(shouldPush[j]).setX(getObject(shouldPush[j]).x() + DIRECTION[i][0]);
      getObject(shouldPush[j]).setY(getObject(shouldPush[j]).y() + DIRECTION[i][1]);
      getObject(shouldPush[j]).setDirection(i);
    }

    for(int j = 0; j < shouldPull.size(); ++j) {
      if(shouldPush.has(shouldPull[j])) {
        continue;
      }
      getObject(shouldPull[j]).setX(getObject(shouldPull[j]).x() + DIRECTION[i][0]);
      getObject(shouldPull[j]).setY(getObject(shouldPull[j]).y() + DIRECTION[i][1]);
      getObject(shouldPull[j]).setDirection(i);
    }
  }
  checkRules();

  // Deal NOUN is NOUN
  Vector nounIsNounRules = getRulesByCondition([&](const CIYRule &rule) {
    return rule.verb() == IS && getGroupByType(rule.object()) == NOUN;
  });
  int preSize = objects.size();
  for(int i = 0; i < preSize; ++i) {
    CIYObject &obj = objects[i];
    bool used = 0;
    for(int j = 0; j < nounIsNounRules.size(); ++j) {
      CIYRule &rule = rules[nounIsNounRules[j]];
      if (objects[i].type() == rule.subject() && rule.subject() != rule.object()) {
        used = 1;
        objects.push(CIYObject(obj.x(), obj.y(), obj.direction(), rule.object()));
        // printf("obj: %d\n", objects.size() - 1);
      }
    }
    if(used) {
      removeObject(i);
    }
  }

  checkRemove();

  // Deal Tele
  Vector objTele = getObjectsByAdj(TELE);
  if (objTele.size() > 1) {
    Vector toTeleZero;
    int i = 0;
    Vector objToTele = getObjectsByPosition(getObject(objTele[i]).x(), getObject(objTele[i]).y());
    for(int k = 0; k < objToTele.size(); k++) {
      if (atSameFloat(objTele[i], objToTele[k]) && objToTele[k] != objTele[i]) {
        toTeleZero.push(objToTele[k]);
      }
    }
    for(i = 1; i < objTele.size(); i++) {
      int j = (i - 1);
      objToTele = getObjectsByPosition(getObject(objTele[i]).x(), getObject(objTele[i]).y());
      for(int k = 0; k < objToTele.size(); k++) {
        if (atSameFloat(objTele[i], objToTele[k]) && objToTele[k] != objTele[i]) {
          getObject(objToTele[k]).setX(getObject(objTele[j]).x());
          getObject(objToTele[k]).setY(getObject(objTele[j]).y());
        }
      }
    }
    for(int k = 0; k < toTeleZero.size(); ++k) {
      getObject(toTeleZero[k]).setX(getObject(objTele[objTele.size() - 1]).x());
      getObject(toTeleZero[k]).setY(getObject(objTele[objTele.size() - 1]).y());
    }
  }

  checkRemove();

  for(int i = 0; i < newObjects.size(); ++i) {
    objects.push(newObjects[i]);
  }

  // Deal Win
  Vector objWin = getObjectsByAdj(WIN);
  objYou = getObjectsByAdj(YOU);
  for(int i = 0; i < objWin.size(); ++i) {
    for(int j = 0; j < objYou.size(); ++j) {
      if (atSameFloat(objWin[i], objYou[j]) && (getObject(objWin[i]).x() == getObject(objYou[j]).x()) && (getObject(objWin[i]).y() == getObject(objYou[j]).y())) {
        isWin = true;
        return;
      }
    }
  }
}
