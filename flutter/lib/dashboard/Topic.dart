import 'package:flutter/material.dart';

class Topic extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Container(
      width: 1130,
      child: Align(
        alignment: Alignment.topCenter,
        child: Text(
          "ระบบคำนวณระบบน้ำตัวอย่าง",
          textAlign: TextAlign.center,
          style: TextStyle(
            fontFamily: 'Itim',
            fontSize: 48,
          ),
        ),
      ),
    );
  }
}
