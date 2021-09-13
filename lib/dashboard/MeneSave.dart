import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';

class MenuSave extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          children: [
            Card(
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(53)),
              color: s2,
              child: Container(
                width: 183,
                height: 196,
                child: Column(
                  children: [
                    Text(
                      "S2",
                      textAlign: TextAlign.center,
                      style: TextStyle(
                        fontFamily: 'Itim',
                        fontSize: 36,
                      ),
                    ),
                    SizedBox(
                      height: 15,
                    ),
                    Text(
                      "2,200 ข้อมูล",
                      textAlign: TextAlign.center,
                      style: TextStyle(
                        fontFamily: 'Itim',
                        fontSize: 18,
                      ),
                    ),
                    SizedBox(
                      height: 8,
                    ),
                    Text(
                      "อัพเดทล่าสุด",
                      textAlign: TextAlign.center,
                      style: TextStyle(
                        fontFamily: 'Itim',
                        fontSize: 18,
                      ),
                    ),
                    SizedBox(
                      height: 8,
                    ),
                    Text(
                      "08/10/2564",
                      textAlign: TextAlign.center,
                      style: TextStyle(
                        fontFamily: 'Itim',
                        fontSize: 18,
                      ),
                    ),
                  ],
                ),
              ),
            ),
            Card(
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(53)),
              color: s3,
              child: Container(
                width: 183,
                height: 196,
                child: Text(
                  "S3",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontFamily: 'Itim',
                    fontSize: 36,
                  ),
                ),
              ),
            ),
            Card(
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(53)),
              color: e1,
              child: Container(
                width: 183,
                height: 196,
                child: Text(
                  "E1",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontFamily: 'Itim',
                    fontSize: 36,
                  ),
                ),
              ),
            ),
          ],
        ),
        SizedBox(
          height: 19,
        ),
        Row(
          children: [
            Container(
              color: savecolor,
              width: 123,
              height: 61,
              child: Text(
                "เพิ่มบันทึก",
                textAlign: TextAlign.center,
                style: TextStyle(
                  color: Colors.white,
                  fontFamily: 'Itim',
                  fontSize: 24,
                ),
              ),
            ),
          ],
        ),
      ],
    );
  }
}
