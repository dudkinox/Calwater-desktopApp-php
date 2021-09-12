import 'dart:math';

import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';

import 'Menu.dart';
import 'Note.dart';

class Dashboard extends StatefulWidget {
  @override
  _DashboardState createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: background,
      body: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          // Menu
          Menu(),
          // Dashboard
          Card(
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(53)),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                mainAxisAlignment: MainAxisAlignment.start,
                children: [
                  Container(
                    width: 1155,
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
                  ),
                  Row(
                    children: [
                      Container(
                        child: Column(
                          children: [
                            Card(
                              color: Colors.black,
                              child: Text("textststst"),
                            ),
                          ],
                        ),
                      ),
                      Container(
                        child: Column(
                          children: [
                            Card(
                              color: Colors.black,
                              child: Text("textststst"),
                            ),
                          ],
                        ),
                      ),
                      Container(
                        child: Column(
                          children: [
                            Card(
                              color: Colors.black,
                              child: Text("textststst"),
                            ),
                          ],
                        ),
                      ),
                    ],
                  ),
                ],
              )),
        ],
      ),
    );
  }
}
