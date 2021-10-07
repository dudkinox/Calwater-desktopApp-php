-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Oct 06, 2021 at 10:11 AM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 8.0.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `calwater`
--

-- --------------------------------------------------------

--
-- Table structure for table `info`
--

CREATE TABLE `info` (
  `ID` int(100) NOT NULL,
  `Volume` decimal(50,9) NOT NULL,
  `Batch_No` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Meet_MOI_Spec` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Sump_No` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Treatment_Date` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `RWWA_ID` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `TWA_ID` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `info`
--

INSERT INTO `info` (`ID`, `Volume`, `Batch_No`, `Meet_MOI_Spec`, `Sump_No`, `Treatment_Date`, `RWWA_ID`, `TWA_ID`) VALUES
(1, '1.000000000', 'S2202101', 'YES', 'S2', '09/22/2021', '1', '1'),
(2, '1.000000000', 'S3202101', 'YES', 'S3', '09/22/2021', '2', '2'),
(3, '1.000000000', 'E1202101', 'YES', 'E1', '09/22/2021', '3', '3'),
(4, '0.123456789', 'S2202102', 'YES', 'S2', '09/22/2021', '4', '4'),
(5, '0.123456789', 'S3202102', 'YES', 'S3', '09/22/2021', '5', '5'),
(6, '0.123456789', 'E1202102', 'YES', 'E1', '09/22/2021', '6', '6'),
(7, '1.000000000', 'S2202103', 'YES', 'S2', '09/23/2021', '7', '7'),
(8, '1.000000000', 'S2202104', 'YES', 'S2', '10/04/2021', '8', '8');

-- --------------------------------------------------------

--
-- Table structure for table `raw_waste_water_analysis`
--

CREATE TABLE `raw_waste_water_analysis` (
  `ID` int(100) NOT NULL,
  `Total_Cr` decimal(50,9) NOT NULL,
  `Cu` decimal(50,9) NOT NULL,
  `Mn` decimal(50,9) NOT NULL,
  `Ni` decimal(50,9) NOT NULL,
  `Pb` decimal(50,9) NOT NULL,
  `Zn` decimal(50,9) NOT NULL,
  `TDS` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `raw_waste_water_analysis`
--

INSERT INTO `raw_waste_water_analysis` (`ID`, `Total_Cr`, `Cu`, `Mn`, `Ni`, `Pb`, `Zn`, `TDS`) VALUES
(1, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(2, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(3, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(4, '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', 0),
(5, '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', 0),
(6, '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', 0),
(7, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(8, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0);

-- --------------------------------------------------------

--
-- Table structure for table `treat_water_analysis`
--

CREATE TABLE `treat_water_analysis` (
  `ID` int(100) NOT NULL,
  `Total_Cr:0.25` decimal(50,9) NOT NULL,
  `Cu:2.0` decimal(50,9) NOT NULL,
  `Mn:5.0` decimal(50,9) NOT NULL,
  `Ni:1.0` decimal(50,9) NOT NULL,
  `Pb:0.2` decimal(50,9) NOT NULL,
  `Zn:5.0` decimal(50,9) NOT NULL,
  `TDS:None` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `treat_water_analysis`
--

INSERT INTO `treat_water_analysis` (`ID`, `Total_Cr:0.25`, `Cu:2.0`, `Mn:5.0`, `Ni:1.0`, `Pb:0.2`, `Zn:5.0`, `TDS:None`) VALUES
(1, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(2, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(3, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(4, '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', 0),
(5, '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', 0),
(6, '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', '0.123456789', 0),
(7, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0),
(8, '2.000000000', '3.000000000', '4.000000000', '5.000000000', '6.000000000', '7.000000000', 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `info`
--
ALTER TABLE `info`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `treat_water_analysis`
--
ALTER TABLE `treat_water_analysis`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `info`
--
ALTER TABLE `info`
  MODIFY `ID` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
