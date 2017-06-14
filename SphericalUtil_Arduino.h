double EARTH_RADIUS = 6371009;

//structure for positions of specific points
typedef struct 
{
    double lt; 
    double ln;
}pos;

double hav(double x) {
        double sinHalf = sin(x * 0.5);
        return sinHalf * sinHalf;
    }

double havDistance(double lat1, double lat2, double dLng) {
        return hav(lat1 - lat2) + hav(dLng) * cos(lat1) * cos(lat2);
    }

double toRadians(double angle) {
   return angle*0.01745329252;
}
double arcHav(double x) {
        return 2 * asin(sqrt(x));
    }

double distanceRadians(double lat1, double lng1, double lat2, double lng2) {
        return arcHav(havDistance(lat1, lat2, lng1 - lng2));
    }

double computeAngleBetween(pos from, pos to) {
        return distanceRadians(toRadians(from.lt), toRadians(from.ln),
                               toRadians(to.lt), toRadians(to.ln));
    }
double computeDistanceBetween(pos from, pos to) {
        return computeAngleBetween(from, to) * EARTH_RADIUS;
    }
pos computeoffset(pos from, double distance, double heading)
{ distance/=EARTH_RADIUS;//earth radious
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


