import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';

class Dashboard extends StatefulWidget {
  @override
  _DashboardState createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: background,
      body: Container(
        margin: const EdgeInsets.only(left: 10.0, top: 10.0),
        child: Image.asset(
          'assets/icon/logo.png',
          height: 100,
          width: 100,
        ),
      ),
    );
  }
}
