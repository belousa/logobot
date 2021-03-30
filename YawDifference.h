class YawDifference {
  int desired;
public:
  explicit YawDifference(int desired) : desired(desired) {}
  
  int turnAngle(int curr) {
        
    auto delta = desired - curr;
 
    if (delta > 180) delta = -(360 - delta);
    else if (delta < -180) delta = 360 + delta;
    
    return delta;
  }

};
