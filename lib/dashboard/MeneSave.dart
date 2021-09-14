import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';

class MenuSave extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          children: [
            SizedBox(
              width: 8,
            ),
            Card(
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(53)),
              color: s2,
              child: Container(
                width: 183,
                height: 196,
                child: Column(
                  children: [
                    SizedBox(
                      height: 10,
                    ),
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
            SizedBox(
              width: 8,
            ),
            Card(
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(53)),
              color: s3,
              child: Container(
                width: 183,
                height: 196,
                child: Column(children: [
                  SizedBox(
                    height: 10,
                  ),
                  Text(
                    "S3",
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
                ]),
              ),
            ),
            SizedBox(
              width: 8,
            ),
            Card(
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(53)),
              color: e1,
              child: Container(
                width: 183,
                height: 196,
                child: Column(children: [
                  SizedBox(
                    height: 10,
                  ),
                  Text(
                    "E1",
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
                ]),
              ),
            ),
            SizedBox(
              height: 19,
            ),
          ],
        ),
        SizedBox(
          height: 20,
        ),
        Container(
          width: 600,
          child: Row(
            children: [
              SizedBox(
                width: 44,
              ),
              Container(
                width: 123,
                height: 61,
                // ignore: deprecated_member_use
                child: RaisedButton(
                  shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(53)),
                  color: savecolor,
                  child: Text(
                    'เพิ่มบันทึก',
                    textAlign: TextAlign.center,
                    style: TextStyle(
                      color: Colors.white,
                      fontFamily: 'Itim',
                      fontSize: 24,
                    ),
                  ),
                  onPressed: () {},
                ),
              ),
              SizedBox(
                width: 77,
              ),
              Container(
                width: 123,
                height: 61,
                // ignore: deprecated_member_use
                child: RaisedButton(
                  shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(53)),
                  color: savecolor,
                  child: Text(
                    'เพิ่มบันทึก',
                    textAlign: TextAlign.center,
                    style: TextStyle(
                      color: Colors.white,
                      fontFamily: 'Itim',
                      fontSize: 24,
                    ),
                  ),
                  onPressed: () {},
                ),
              ),
              SizedBox(
                width: 76,
              ),
              Container(
                width: 123,
                height: 61,
                // ignore: deprecated_member_use
                child: RaisedButton(
                  shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(53)),
                  color: savecolor,
                  child: Text(
                    'เพิ่มบันทึก',
                    textAlign: TextAlign.center,
                    style: TextStyle(
                      color: Colors.white,
                      fontFamily: 'Itim',
                      fontSize: 24,
                    ),
                  ),
                  onPressed: () {},
                ),
              ),
            ],
          ),
        ),
      ],
    );
  }
}
