import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';

class Menu extends StatefulWidget {
  @override
  _MenuState createState() => _MenuState();
}

class _MenuState extends State<Menu> {
  @override
  Widget build(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: <Widget>[
        Container(
          margin: const EdgeInsets.only(left: 10.0, top: 30.0),
          child: IconButton(
            icon: Image.asset('assets/icon/logo.png'),
            iconSize: 100,
            splashColor: Colors.white,
            onPressed: () {},
          ),
        ),
        Container(
          width: 115,
          height: 10,
          child: Divider(
            indent: 18,
            endIndent: 0,
            color: dividercolor,
          ),
        ),
        Container(
          margin: const EdgeInsets.only(left: 17.0, top: 10.0),
          child: IconButton(
            icon: Image.asset('assets/icon/adddata.png'),
            iconSize: 75,
            splashColor: Colors.white,
            onPressed: () {},
          ),
        ),
        Text(
          'Add data',
          textAlign: TextAlign.center,
          style: TextStyle(
            fontFamily: 'Itim',
            fontSize: 22,
          ),
        ),
        Container(
          margin: const EdgeInsets.only(left: 17.0, top: 10.0),
          child: IconButton(
            icon: Image.asset('assets/icon/chart.png'),
            iconSize: 65,
            splashColor: Colors.white,
            onPressed: () {},
          ),
        ),
        Text(
          'chart',
          textAlign: TextAlign.center,
          style: TextStyle(
            fontFamily: 'Itim',
            fontSize: 22,
          ),
        ),
      ],
    );
  }
}
