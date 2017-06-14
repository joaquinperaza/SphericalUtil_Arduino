
pos computeoffset(pos from, double distance, double heading)
{ distance/=6371009;//earth radious
  heading*=0.01745329252;
  double fromLat = from.lt*0.01745329252;
  double fromLng = from.ln*0.01745329252;
  double cosDistance = cos(distance);
  double sinDistance = sin(distance);
  double sinFromLat = sin(fromLat);
  double cosFromLat = cos(fromLat);
  double sinLat = cosDistance * sinFromLat + sinDistance * cosFromLat * cos(heading);
  double dLng = atan2(
                sinDistance * cosFromLat * sin(heading),
                cosDistance - sinFromLat * sinLat);
  pos offset;
  offset.lt=(asin(sinLat))/0.01745329252;
  offset.ln=(fromLng + dLng)/0.01745329252;
  return offset;
}


//structure for positions of specific points
typedef struct 
{
    double lt; 
    double ln;
}pos;


