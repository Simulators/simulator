<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="16" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="14" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="tplace-old" color="10" fill="1" visible="yes" active="yes"/>
<layer number="109" name="ref-old" color="11" fill="1" visible="yes" active="yes"/>
<layer number="110" name="fp0" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="LPC17xx" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="IDFDebug" color="7" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="no" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="154" name="FabDoc2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="155" name="FabDoc3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="225" name="225bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="226" name="226bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="227" name="227bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="228" name="228bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="229" name="229bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="230" name="230bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="231" name="231bmp" color="7" fill="1" visible="no" active="yes"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="routoute" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="SparkFun-Connectors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find connectors and sockets- basically anything that can be plugged into or onto.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="1X03">
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="6.35" y1="0.635" x2="6.35" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="MOLEX-1X3">
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="6.35" y1="3.048" x2="6.35" y2="-2.54" width="0.127" layer="21"/>
<wire x1="6.35" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="6.35" y1="-2.54" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="5.08" y2="-1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="-1.27" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796"/>
</package>
<package name="SCREWTERMINAL-3.5MM-3">
<wire x1="-2.3" y1="3.4" x2="9.3" y2="3.4" width="0.2032" layer="21"/>
<wire x1="9.3" y1="3.4" x2="9.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="9.3" y1="-2.8" x2="9.3" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="9.3" y1="-3.6" x2="-2.3" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-3.6" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-2.8" x2="-2.3" y2="3.4" width="0.2032" layer="21"/>
<wire x1="9.3" y1="-2.8" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.35" x2="-2.7" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-1.35" x2="-2.7" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-2.35" x2="-2.3" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="9.3" y1="3.15" x2="9.7" y2="3.15" width="0.2032" layer="51"/>
<wire x1="9.7" y1="3.15" x2="9.7" y2="2.15" width="0.2032" layer="51"/>
<wire x1="9.7" y1="2.15" x2="9.3" y2="2.15" width="0.2032" layer="51"/>
<pad name="1" x="0" y="0" drill="1.2" diameter="2.413" shape="square"/>
<pad name="2" x="3.5" y="0" drill="1.2" diameter="2.413"/>
<pad name="3" x="7" y="0" drill="1.2" diameter="2.413"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X03_LOCK">
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="6.35" y1="0.635" x2="6.35" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="1X03_LOCK_LONGPADS">
<description>This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place.  
You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  
This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" 
to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers.
Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,
if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<wire x1="1.524" y1="-0.127" x2="1.016" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="4.064" y1="-0.127" x2="3.556" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.016" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.27" y2="0.8636" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.8636" x2="-0.9906" y2="1.143" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.27" y2="-1.1176" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.1176" x2="-0.9906" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.127" x2="6.096" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.127" x2="6.35" y2="-1.1176" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-1.1176" x2="6.0706" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.127" x2="6.35" y2="0.8636" width="0.2032" layer="21"/>
<wire x1="6.35" y1="0.8636" x2="6.0706" y2="1.143" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="-0.254" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-1.27" y="1.778" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-3.302" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.4191" x2="0.2921" y2="0.1651" layer="51"/>
<rectangle x1="2.2479" y1="-0.4191" x2="2.8321" y2="0.1651" layer="51"/>
<rectangle x1="4.7879" y1="-0.4191" x2="5.3721" y2="0.1651" layer="51"/>
</package>
<package name="MOLEX-1X3_LOCK">
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="6.35" y1="3.048" x2="6.35" y2="-2.54" width="0.127" layer="21"/>
<wire x1="6.35" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="6.35" y1="-2.54" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="5.08" y2="-1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="-1.27" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="0" y="0.127" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" diameter="1.8796"/>
<rectangle x1="-0.2921" y1="-0.2921" x2="0.2921" y2="0.2921" layer="51"/>
<rectangle x1="2.2479" y1="-0.2921" x2="2.8321" y2="0.2921" layer="51"/>
<rectangle x1="4.7879" y1="-0.2921" x2="5.3721" y2="0.2921" layer="51"/>
</package>
<package name="SCREWTERMINAL-3.5MM-3_LOCK.007S">
<wire x1="-2.3" y1="3.4" x2="9.3" y2="3.4" width="0.2032" layer="21"/>
<wire x1="9.3" y1="3.4" x2="9.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="9.3" y1="-2.8" x2="9.3" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="9.3" y1="-3.6" x2="-2.3" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-3.6" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-2.8" x2="-2.3" y2="3.4" width="0.2032" layer="21"/>
<wire x1="9.3" y1="-2.8" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.35" x2="-2.7" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-1.35" x2="-2.7" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-2.35" x2="-2.3" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="9.3" y1="3.15" x2="9.7" y2="3.15" width="0.2032" layer="51"/>
<wire x1="9.7" y1="3.15" x2="9.7" y2="2.15" width="0.2032" layer="51"/>
<wire x1="9.7" y1="2.15" x2="9.3" y2="2.15" width="0.2032" layer="51"/>
<circle x="0" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="3.5" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="7" y="0" radius="0.425" width="0.001" layer="51"/>
<pad name="1" x="-0.1778" y="0" drill="1.2" diameter="2.032" shape="square"/>
<pad name="2" x="3.5" y="0" drill="1.2" diameter="2.032"/>
<pad name="3" x="7.1778" y="0" drill="1.2" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X03_NO_SILK">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="1X03_LONGPADS">
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="0.635" x2="6.35" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<text x="-1.3462" y="2.4638" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="JST-3-PTH">
<wire x1="-3.95" y1="-1.6" x2="-3.95" y2="6" width="0.2032" layer="21"/>
<wire x1="-3.95" y1="6" x2="3.95" y2="6" width="0.2032" layer="21"/>
<wire x1="3.95" y1="6" x2="3.95" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-3.95" y1="-1.6" x2="-3.3" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="3.95" y1="-1.6" x2="3.3" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="-1.6" x2="-3.3" y2="0" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-1.6" x2="3.3" y2="0" width="0.2032" layer="21"/>
<pad name="1" x="-2" y="0" drill="0.7" diameter="1.6"/>
<pad name="2" x="0" y="0" drill="0.7" diameter="1.6"/>
<pad name="3" x="2" y="0" drill="0.7" diameter="1.6"/>
<text x="-1.27" y="5.24" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="3.97" size="0.4064" layer="27">&gt;Value</text>
<text x="-2.4" y="0.67" size="1.27" layer="51">+</text>
<text x="-0.4" y="0.67" size="1.27" layer="51">-</text>
<text x="1.7" y="0.87" size="0.8" layer="51">S</text>
</package>
<package name="1X03_PP_HOLES_ONLY">
<circle x="0" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="2.54" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="5.08" y="0" radius="0.635" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="0.9" diameter="0.8128" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="0.9" diameter="0.8128" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="0.9" diameter="0.8128" rot="R90"/>
<hole x="0" y="0" drill="1.4732"/>
<hole x="2.54" y="0" drill="1.4732"/>
<hole x="5.08" y="0" drill="1.4732"/>
</package>
<package name="SCREWTERMINAL-5MM-3">
<wire x1="-3.1" y1="4.2" x2="13.1" y2="4.2" width="0.2032" layer="21"/>
<wire x1="13.1" y1="4.2" x2="13.1" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="13.1" y1="-2.3" x2="13.1" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="13.1" y1="-3.3" x2="-3.1" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-3.3" x2="-3.1" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-2.3" x2="-3.1" y2="4.2" width="0.2032" layer="21"/>
<wire x1="13.1" y1="-2.3" x2="-3.1" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-1.35" x2="-3.7" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-3.7" y1="-1.35" x2="-3.7" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-3.7" y1="-2.35" x2="-3.1" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="13.1" y1="4" x2="13.7" y2="4" width="0.2032" layer="51"/>
<wire x1="13.7" y1="4" x2="13.7" y2="3" width="0.2032" layer="51"/>
<wire x1="13.7" y1="3" x2="13.1" y2="3" width="0.2032" layer="51"/>
<circle x="2.5" y="3.7" radius="0.2828" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="1.3" diameter="2.413" shape="square"/>
<pad name="2" x="5" y="0" drill="1.3" diameter="2.413"/>
<pad name="3" x="10" y="0" drill="1.3" diameter="2.413"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X03_LOCK_NO_SILK">
<pad name="1" x="0" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="JST-3-SMD">
<wire x1="-4.99" y1="-2.07" x2="-4.99" y2="-5.57" width="0.2032" layer="21"/>
<wire x1="-4.99" y1="-5.57" x2="-4.19" y2="-5.57" width="0.2032" layer="21"/>
<wire x1="-4.19" y1="-5.57" x2="-4.19" y2="-3.07" width="0.2032" layer="21"/>
<wire x1="-4.19" y1="-3.07" x2="-2.99" y2="-3.07" width="0.2032" layer="21"/>
<wire x1="3.01" y1="-3.07" x2="4.21" y2="-3.07" width="0.2032" layer="21"/>
<wire x1="4.21" y1="-3.07" x2="4.21" y2="-5.57" width="0.2032" layer="21"/>
<wire x1="4.21" y1="-5.57" x2="5.01" y2="-5.57" width="0.2032" layer="21"/>
<wire x1="5.01" y1="-5.57" x2="5.01" y2="-2.07" width="0.2032" layer="21"/>
<wire x1="3.01" y1="1.93" x2="-2.99" y2="1.93" width="0.2032" layer="21"/>
<smd name="1" x="-1.99" y="-4.77" dx="1" dy="4.6" layer="1"/>
<smd name="3" x="2.01" y="-4.77" dx="1" dy="4.6" layer="1"/>
<smd name="NC1" x="-4.39" y="0.43" dx="3.4" dy="1.6" layer="1" rot="R90"/>
<smd name="NC2" x="4.41" y="0.43" dx="3.4" dy="1.6" layer="1" rot="R90"/>
<smd name="2" x="0.01" y="-4.77" dx="1" dy="4.6" layer="1"/>
<text x="-2.26" y="0.2" size="0.4064" layer="25">&gt;Name</text>
<text x="-2.26" y="-1.07" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="1X03-1MM-RA">
<wire x1="-1" y1="-4.6" x2="1" y2="-4.6" width="0.254" layer="21"/>
<wire x1="-2.5" y1="-2" x2="-2.5" y2="-0.35" width="0.254" layer="21"/>
<wire x1="1.75" y1="-0.35" x2="2.4997" y2="-0.35" width="0.254" layer="21"/>
<wire x1="2.4997" y1="-0.35" x2="2.4997" y2="-2" width="0.254" layer="21"/>
<wire x1="-2.5" y1="-0.35" x2="-1.75" y2="-0.35" width="0.254" layer="21"/>
<circle x="-2" y="0.3" radius="0.1414" width="0.4" layer="21"/>
<smd name="NC2" x="-2.3" y="-3.675" dx="1.2" dy="2" layer="1"/>
<smd name="NC1" x="2.3" y="-3.675" dx="1.2" dy="2" layer="1"/>
<smd name="1" x="-1" y="0" dx="0.6" dy="1.35" layer="1"/>
<smd name="2" x="0" y="0" dx="0.6" dy="1.35" layer="1"/>
<smd name="3" x="1" y="0" dx="0.6" dy="1.35" layer="1"/>
<text x="-1.73" y="1.73" size="0.4064" layer="25" rot="R180">&gt;NAME</text>
<text x="3.46" y="1.73" size="0.4064" layer="27" rot="R180">&gt;VALUE</text>
</package>
<package name="1X03_SMD_RA_FEMALE">
<wire x1="-3.935" y1="4.25" x2="-3.935" y2="-4.25" width="0.1778" layer="21"/>
<wire x1="3.935" y1="4.25" x2="-3.935" y2="4.25" width="0.1778" layer="21"/>
<wire x1="3.935" y1="-4.25" x2="3.935" y2="4.25" width="0.1778" layer="21"/>
<wire x1="-3.935" y1="-4.25" x2="3.935" y2="-4.25" width="0.1778" layer="21"/>
<rectangle x1="-0.32" y1="6.8" x2="0.32" y2="7.65" layer="51"/>
<rectangle x1="2.22" y1="6.8" x2="2.86" y2="7.65" layer="51"/>
<rectangle x1="-2.86" y1="6.8" x2="-2.22" y2="7.65" layer="51"/>
<smd name="3" x="2.54" y="7.225" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="2" x="0" y="7.225" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="1" x="-2.54" y="7.225" dx="1.25" dy="3" layer="1" rot="R180"/>
<text x="-3.155" y="2.775" size="1" layer="27">&gt;Value</text>
<text x="-2.955" y="-3.395" size="1" layer="25">&gt;Name</text>
</package>
<package name="1X03_SMD_RA_MALE">
<wire x1="3.81" y1="1.25" x2="-3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="-3.81" y1="1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="2.53" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="-0.01" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-2.55" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="2.53" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-0.01" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-2.55" y2="-7.25" width="0.127" layer="51"/>
<rectangle x1="-0.32" y1="4.15" x2="0.32" y2="5.95" layer="51"/>
<rectangle x1="-2.86" y1="4.15" x2="-2.22" y2="5.95" layer="51"/>
<rectangle x1="2.22" y1="4.15" x2="2.86" y2="5.95" layer="51"/>
<smd name="1" x="-2.54" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="2" x="0" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="3" x="2.54" y="5" dx="3" dy="1" layer="1" rot="R90"/>
</package>
<package name="1X03_SMD_RA_MALE_POST">
<description>&lt;h3&gt;SMD 3-Pin Male Right-Angle Header w/ Alignment posts&lt;/h3&gt;

Matches 4UCONN part # 11026&lt;br&gt;
&lt;a href="http://www.4uconnector.com/online/object/4udrawing/11026.pdf"&gt;http://www.4uconnector.com/online/object/4udrawing/11026.pdf&lt;/a&gt;</description>
<wire x1="3.81" y1="1.25" x2="-3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="-3.81" y1="1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="2.53" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="-0.01" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-2.55" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="2.53" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-0.01" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-2.55" y2="-7.25" width="0.127" layer="51"/>
<rectangle x1="-0.32" y1="4.15" x2="0.32" y2="5.95" layer="51"/>
<rectangle x1="-2.86" y1="4.15" x2="-2.22" y2="5.95" layer="51"/>
<rectangle x1="2.22" y1="4.15" x2="2.86" y2="5.95" layer="51"/>
<smd name="1" x="-2.54" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<smd name="2" x="0" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<smd name="3" x="2.54" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<hole x="-1.27" y="0" drill="1.6"/>
<hole x="1.27" y="0" drill="1.6"/>
</package>
<package name="JST-3-PTH-VERT">
<description>This 3-pin connector mates with the JST cable sold on SparkFun.</description>
<wire x1="-3.95" y1="-2.25" x2="-3.95" y2="2.25" width="0.2032" layer="21"/>
<wire x1="-3.95" y1="2.25" x2="3.95" y2="2.25" width="0.2032" layer="21"/>
<wire x1="3.95" y1="2.25" x2="3.95" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="3.95" y1="-2.25" x2="1" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-2.25" x2="-3.95" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-1.75" x2="1" y2="-1.75" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.75" x2="1" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-1.75" x2="-1" y2="-2.25" width="0.2032" layer="21"/>
<pad name="1" x="-2" y="-0.55" drill="0.7" diameter="1.6"/>
<pad name="2" x="0" y="-0.55" drill="0.7" diameter="1.6"/>
<pad name="3" x="2" y="-0.55" drill="0.7" diameter="1.6"/>
<text x="-3" y="3" size="0.4064" layer="25">&gt;Name</text>
<text x="1" y="3" size="0.4064" layer="27">&gt;Value</text>
<text x="-2.4" y="0.75" size="1.27" layer="51">+</text>
<text x="-0.4" y="0.75" size="1.27" layer="51">-</text>
<text x="1.7" y="0.95" size="0.8" layer="51">S</text>
</package>
<package name="1X03_SMD_RA_MALE_POST_SMALLER">
<wire x1="3.81" y1="1.25" x2="-3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="-3.81" y1="1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="2.53" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="-0.01" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-2.55" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="2.53" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-0.01" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-2.55" y2="-7.25" width="0.127" layer="51"/>
<rectangle x1="-0.32" y1="4.15" x2="0.32" y2="5.95" layer="51"/>
<rectangle x1="-2.86" y1="4.15" x2="-2.22" y2="5.95" layer="51"/>
<rectangle x1="2.22" y1="4.15" x2="2.86" y2="5.95" layer="51"/>
<smd name="1" x="-2.54" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<smd name="2" x="0" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<smd name="3" x="2.54" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<hole x="-1.27" y="0" drill="1.3589"/>
<hole x="1.27" y="0" drill="1.3589"/>
</package>
<package name="1X03_SMD_RA_MALE_POST_SMALLEST">
<wire x1="3.81" y1="1.25" x2="-3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="-3.81" y1="1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="2.53" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="-0.01" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-2.55" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-3.81" y2="-1.25" width="0.1778" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="3.81" y2="1.25" width="0.1778" layer="51"/>
<wire x1="2.53" y1="-1.25" x2="2.53" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-0.01" y1="-1.25" x2="-0.01" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-2.55" y1="-1.25" x2="-2.55" y2="-7.25" width="0.127" layer="51"/>
<rectangle x1="-0.32" y1="4.15" x2="0.32" y2="5.95" layer="51"/>
<rectangle x1="-2.86" y1="4.15" x2="-2.22" y2="5.95" layer="51"/>
<rectangle x1="2.22" y1="4.15" x2="2.86" y2="5.95" layer="51"/>
<smd name="1" x="-2.54" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<smd name="2" x="0" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<smd name="3" x="2.54" y="5.07" dx="2.5" dy="1.27" layer="1" rot="R90"/>
<hole x="-1.27" y="0" drill="1.3462"/>
<hole x="1.27" y="0" drill="1.3462"/>
</package>
</packages>
<symbols>
<symbol name="M03">
<wire x1="3.81" y1="-5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<text x="-2.54" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="5.842" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="M03" prefix="JP" uservalue="yes">
<description>&lt;b&gt;Header 3&lt;/b&gt;
Standard 3-pin 0.1" header. Use with straight break away headers (SKU : PRT-00116), right angle break away headers (PRT-00553), swiss pins (PRT-00743), machine pins (PRT-00117), and female headers (PRT-00115). Molex polarized connector foot print use with SKU : PRT-08232 with associated crimp pins and housings.</description>
<gates>
<gate name="G$1" symbol="M03" x="-2.54" y="0"/>
</gates>
<devices>
<device name="PTH" package="1X03">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POLAR" package="MOLEX-1X3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SCREW" package="SCREWTERMINAL-3.5MM-3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LOCK" package="1X03_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LOCK_LONGPADS" package="1X03_LOCK_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POLAR_LOCK" package="MOLEX-1X3_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SCREW_LOCK" package="SCREWTERMINAL-3.5MM-3_LOCK.007S">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1X03_NO_SILK" package="1X03_NO_SILK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LONGPADS" package="1X03_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST-PTH" package="JST-3-PTH">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="SKU" value="PRT-09915" constant="no"/>
</technology>
</technologies>
</device>
<device name="POGO_PIN_HOLES_ONLY" package="1X03_PP_HOLES_ONLY">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-SCREW-5MM" package="SCREWTERMINAL-5MM-3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="STOREFRONT_ID" value="PRT-08433" constant="no"/>
</technology>
</technologies>
</device>
<device name="LOCK_NO_SILK" package="1X03_LOCK_NO_SILK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST-SMD" package="JST-3-SMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="1X03-1MM-RA">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD_RA_FEMALE" package="1X03_SMD_RA_FEMALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-10926"/>
<attribute name="VALUE" value="1x3 RA Female .1&quot;"/>
</technology>
</technologies>
</device>
<device name="SMD_RA_MALE" package="1X03_SMD_RA_MALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-10925"/>
</technology>
</technologies>
</device>
<device name="SMD_RA_MALE_POST" package="1X03_SMD_RA_MALE_POST">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST-PTH-VERT" package="JST-3-PTH-VERT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1X03_SMD_RA_MALE_POST_SMALLER" package="1X03_SMD_RA_MALE_POST_SMALLER">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1X03_SMD_RA_MALE_POST_SMALLEST" package="1X03_SMD_RA_MALE_POST_SMALLEST">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Aesthetics">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find non-functional items- supply symbols, logos, notations, frame blocks, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
</packages>
<symbols>
<symbol name="FR-A4L">
<rectangle x1="178.7652" y1="0" x2="179.3748" y2="20.32" layer="94"/>
<rectangle x1="225.7552" y1="-26.67" x2="226.3648" y2="67.31" layer="94" rot="R90"/>
<wire x1="225.29" y1="-0.1" x2="225.29" y2="5.08" width="0.1016" layer="94"/>
<wire x1="225.29" y1="5.08" x2="273.05" y2="5.08" width="0.1016" layer="94"/>
<wire x1="225.29" y1="5.08" x2="179.07" y2="5.08" width="0.1016" layer="94"/>
<wire x1="179.07" y1="10.16" x2="225.29" y2="10.16" width="0.1016" layer="94"/>
<wire x1="225.29" y1="10.16" x2="273.05" y2="10.16" width="0.1016" layer="94"/>
<wire x1="179.07" y1="15.24" x2="273.05" y2="15.24" width="0.1016" layer="94"/>
<wire x1="225.29" y1="5.08" x2="225.29" y2="10.16" width="0.1016" layer="94"/>
<wire x1="179.07" y1="19.05" x2="179.07" y2="20.32" width="0.6096" layer="94"/>
<wire x1="179.07" y1="20.32" x2="180.34" y2="20.32" width="0.6096" layer="94"/>
<text x="181.61" y="11.43" size="2.54" layer="94" font="vector">&gt;DRAWING_NAME</text>
<text x="181.61" y="6.35" size="2.286" layer="94" font="vector">&gt;LAST_DATE_TIME</text>
<text x="195.58" y="1.27" size="2.54" layer="94" font="vector">&gt;SHEET</text>
<text x="181.61" y="1.27" size="2.54" layer="94" font="vector">Sheet:</text>
<text x="181.61" y="16.51" size="2.54" layer="94" font="vector">&gt;CNAME</text>
<text x="226.16" y="1.27" size="2.54" layer="94" font="vector">Rev:</text>
<text x="226.26" y="6.35" size="2.54" layer="94" font="vector">&gt;DESIGNER</text>
<text x="234.92" y="1.17" size="2.54" layer="94" font="vector">&gt;CREVISION</text>
<frame x1="-3.81" y1="-3.81" x2="276.86" y2="182.88" columns="8" rows="5" layer="94"/>
</symbol>
<symbol name="DGND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="VCC">
<wire x1="0.762" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="-0.762" y2="1.27" width="0.254" layer="94"/>
<text x="-1.016" y="3.556" size="1.778" layer="96">&gt;VALUE</text>
<pin name="VCC" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME-A4L" prefix="FRAME">
<description>&lt;b&gt;Schematic Frame-European Format&lt;/b&gt;
&lt;br&gt;&lt;br&gt;
Standard A4 size frame in Landscape</description>
<gates>
<gate name="G$1" symbol="FR-A4L" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="DGND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VCC" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="VCC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="st-microelectronics">
<description>&lt;b&gt;ST Microelectronics Devices&lt;/b&gt;&lt;p&gt;
Microcontrollers,  I2C components, linear devices&lt;p&gt;
http://www.st.com&lt;p&gt;
&lt;i&gt;Include st-microelectronics-2.lbr, st-microelectronics-3.lbr.&lt;p&gt;&lt;/i&gt;

&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SO08">
<description>&lt;b&gt;SMALL OUTLINE INTEGRATED CIRCUIT&lt;/b&gt;&lt;p&gt;
body 3.9 mm/JEDEC MS-012AA</description>
<wire x1="-2.9" y1="3.9" x2="2.9" y2="3.9" width="0.1998" layer="39"/>
<wire x1="2.9" y1="3.9" x2="2.9" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="2.9" y1="-3.9" x2="-2.9" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="-2.9" y1="-3.9" x2="-2.9" y2="3.9" width="0.1998" layer="39"/>
<wire x1="2.4" y1="1.9" x2="2.4" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.4" x2="2.4" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.9" x2="-2.4" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="-1.9" x2="-2.4" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="-1.4" x2="-2.4" y2="1.9" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="1.9" x2="2.4" y2="1.9" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.4" x2="-2.4" y2="-1.4" width="0.2032" layer="51"/>
<smd name="2" x="-0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="-0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="-1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-3.175" y="-1.905" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="4.445" y="-1.905" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-2.1501" y1="-3.1001" x2="-1.6599" y2="-2" layer="51"/>
<rectangle x1="-0.8801" y1="-3.1001" x2="-0.3899" y2="-2" layer="51"/>
<rectangle x1="0.3899" y1="-3.1001" x2="0.8801" y2="-2" layer="51"/>
<rectangle x1="1.6599" y1="-3.1001" x2="2.1501" y2="-2" layer="51"/>
<rectangle x1="1.6599" y1="2" x2="2.1501" y2="3.1001" layer="51"/>
<rectangle x1="0.3899" y1="2" x2="0.8801" y2="3.1001" layer="51"/>
<rectangle x1="-0.8801" y1="2" x2="-0.3899" y2="3.1001" layer="51"/>
<rectangle x1="-2.1501" y1="2" x2="-1.6599" y2="3.1001" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="USB6B1">
<wire x1="-5.08" y1="5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="-7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="2.54" x2="-3.81" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="0" x2="-3.81" y2="0" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-3.81" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-3.81" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="3.81" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="3.81" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0" x2="3.81" y2="0" width="0.1524" layer="94"/>
<wire x1="5.08" y1="2.54" x2="3.81" y2="2.54" width="0.1524" layer="94"/>
<text x="-5.08" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-9.8425" size="1.778" layer="96">&gt;VALUE</text>
<pin name="VCC" x="-7.62" y="2.54" length="short" direction="pwr"/>
<pin name="IO1" x="-7.62" y="0" length="short"/>
<pin name="IO2" x="-7.62" y="-2.54" length="short"/>
<pin name="GND" x="-7.62" y="-5.08" length="short" direction="pwr"/>
<pin name="GND@2" x="7.62" y="-5.08" visible="pad" length="short" direction="pwr" rot="R180"/>
<pin name="IO2@2" x="7.62" y="-2.54" visible="pad" length="short" rot="R180"/>
<pin name="IO1@2" x="7.62" y="0" visible="pad" length="short" rot="R180"/>
<pin name="VCC@2" x="7.62" y="2.54" visible="pad" length="short" direction="pwr" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="USB6B1" prefix="IC">
<description>&lt;b&gt;DATA LINES PROTECTION&lt;br&gt;&lt;/b&gt;&lt;p&gt;
Source: http://www.st.com/stonline/products/literature/ds/5605.pdf</description>
<gates>
<gate name="G$1" symbol="USB6B1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SO08">
<connects>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="GND@2" pad="5"/>
<connect gate="G$1" pin="IO1" pad="2"/>
<connect gate="G$1" pin="IO1@2" pad="7"/>
<connect gate="G$1" pin="IO2" pad="3"/>
<connect gate="G$1" pin="IO2@2" pad="6"/>
<connect gate="G$1" pin="VCC" pad="1"/>
<connect gate="G$1" pin="VCC@2" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="USB6B1" constant="no"/>
<attribute name="OC_FARNELL" value="9804358" constant="no"/>
<attribute name="OC_NEWARK" value="26M4750" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="B7" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="FRAME1" library="SparkFun-Aesthetics" deviceset="FRAME-A4L" device="">
<attribute name="CNAME" value="Simulator Interface TVS Board"/>
<attribute name="CREVISION" value="A 04/2016"/>
<attribute name="DESIGNER" value="A J Instone-Cowie"/>
</part>
<part name="B9" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="BE" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B1" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B3" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B5" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B8" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B0" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="BT" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B2" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B4" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="B6" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY3" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY1" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY4" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY5" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY6" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY7" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY8" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY9" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY10" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY11" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY12" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY13" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND1" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND3" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND4" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND5" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND6" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND7" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND8" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND9" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND10" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND11" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND12" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND13" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S1" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY2" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND2" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S2" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY16" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND14" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S3" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY17" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND15" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S4" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY18" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND16" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S5" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY19" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND17" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S6" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY20" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND18" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S7" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY21" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND19" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S8" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY22" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND20" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S9" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY23" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND21" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="S0" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY24" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND22" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="SE" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY25" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND23" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="ST" library="SparkFun-Connectors" deviceset="M03" device="PTH"/>
<part name="SUPPLY26" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="GND24" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="IC1" library="st-microelectronics" deviceset="USB6B1" device=""/>
<part name="IC2" library="st-microelectronics" deviceset="USB6B1" device=""/>
<part name="IC3" library="st-microelectronics" deviceset="USB6B1" device=""/>
<part name="GND25" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND26" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND27" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND28" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND29" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND30" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="SUPPLY27" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY28" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY29" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY30" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY31" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY32" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="IC4" library="st-microelectronics" deviceset="USB6B1" device=""/>
<part name="IC5" library="st-microelectronics" deviceset="USB6B1" device=""/>
<part name="IC6" library="st-microelectronics" deviceset="USB6B1" device=""/>
<part name="GND31" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND32" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND33" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND34" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND35" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="GND36" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="SUPPLY33" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY34" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY35" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY36" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY37" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
<part name="SUPPLY38" library="SparkFun-Aesthetics" deviceset="VCC" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="10.16" y="12.7" size="1.778" layer="94" font="vector">This design is released under the Creative Commons Attribution-ShareAlike 4.0 International License (CC BY-SA)</text>
</plain>
<instances>
<instance part="B7" gate="G$1" x="243.84" y="162.56" rot="R180"/>
<instance part="FRAME1" gate="G$1" x="5.08" y="7.62">
<attribute name="DESIGNER" x="5.08" y="7.62" size="1.778" layer="96" display="off"/>
<attribute name="CREVISION" x="5.08" y="7.62" size="1.778" layer="96" display="off"/>
<attribute name="CNAME" x="5.08" y="7.62" size="1.778" layer="96" display="off"/>
</instance>
<instance part="B9" gate="G$1" x="243.84" y="121.92" rot="R180"/>
<instance part="BE" gate="G$1" x="243.84" y="81.28" rot="R180"/>
<instance part="B1" gate="G$1" x="124.46" y="162.56" rot="R180"/>
<instance part="B3" gate="G$1" x="124.46" y="121.92" rot="R180"/>
<instance part="B5" gate="G$1" x="124.46" y="81.28" rot="R180"/>
<instance part="B8" gate="G$1" x="243.84" y="142.24" rot="R180"/>
<instance part="B0" gate="G$1" x="243.84" y="101.6" rot="R180"/>
<instance part="BT" gate="G$1" x="243.84" y="58.42" rot="R180"/>
<instance part="B2" gate="G$1" x="124.46" y="142.24" rot="R180"/>
<instance part="B4" gate="G$1" x="124.46" y="101.6" rot="R180"/>
<instance part="B6" gate="G$1" x="124.46" y="58.42" rot="R180"/>
<instance part="SUPPLY3" gate="G$1" x="233.68" y="165.1"/>
<instance part="SUPPLY1" gate="G$1" x="233.68" y="144.78"/>
<instance part="SUPPLY4" gate="G$1" x="233.68" y="104.14"/>
<instance part="SUPPLY5" gate="G$1" x="233.68" y="124.46"/>
<instance part="SUPPLY6" gate="G$1" x="233.68" y="83.82"/>
<instance part="SUPPLY7" gate="G$1" x="233.68" y="60.96"/>
<instance part="SUPPLY8" gate="G$1" x="114.3" y="165.1"/>
<instance part="SUPPLY9" gate="G$1" x="114.3" y="144.78"/>
<instance part="SUPPLY10" gate="G$1" x="114.3" y="124.46"/>
<instance part="SUPPLY11" gate="G$1" x="114.3" y="104.14"/>
<instance part="SUPPLY12" gate="G$1" x="114.3" y="83.82"/>
<instance part="SUPPLY13" gate="G$1" x="114.3" y="60.96"/>
<instance part="GND1" gate="1" x="228.6" y="167.64" rot="R180"/>
<instance part="GND3" gate="1" x="228.6" y="127" rot="R180"/>
<instance part="GND4" gate="1" x="228.6" y="86.36" rot="R180"/>
<instance part="GND5" gate="1" x="228.6" y="147.32" rot="R180"/>
<instance part="GND6" gate="1" x="228.6" y="106.68" rot="R180"/>
<instance part="GND7" gate="1" x="228.6" y="63.5" rot="R180"/>
<instance part="GND8" gate="1" x="109.22" y="147.32" rot="R180"/>
<instance part="GND9" gate="1" x="109.22" y="127" rot="R180"/>
<instance part="GND10" gate="1" x="109.22" y="106.68" rot="R180"/>
<instance part="GND11" gate="1" x="109.22" y="63.5" rot="R180"/>
<instance part="GND12" gate="1" x="109.22" y="86.36" rot="R180"/>
<instance part="GND13" gate="1" x="109.22" y="167.64" rot="R180"/>
<instance part="S1" gate="G$1" x="40.64" y="162.56" rot="MR180"/>
<instance part="SUPPLY2" gate="G$1" x="50.8" y="165.1" rot="MR0"/>
<instance part="GND2" gate="1" x="55.88" y="167.64" rot="MR180"/>
<instance part="S2" gate="G$1" x="40.64" y="142.24" rot="MR180"/>
<instance part="SUPPLY16" gate="G$1" x="50.8" y="144.78" rot="MR0"/>
<instance part="GND14" gate="1" x="55.88" y="147.32" rot="MR180"/>
<instance part="S3" gate="G$1" x="40.64" y="121.92" rot="MR180"/>
<instance part="SUPPLY17" gate="G$1" x="50.8" y="124.46" rot="MR0"/>
<instance part="GND15" gate="1" x="55.88" y="127" rot="MR180"/>
<instance part="S4" gate="G$1" x="40.64" y="101.6" rot="MR180"/>
<instance part="SUPPLY18" gate="G$1" x="50.8" y="104.14" rot="MR0"/>
<instance part="GND16" gate="1" x="55.88" y="106.68" rot="MR180"/>
<instance part="S5" gate="G$1" x="40.64" y="81.28" rot="MR180"/>
<instance part="SUPPLY19" gate="G$1" x="50.8" y="83.82" rot="MR0"/>
<instance part="GND17" gate="1" x="55.88" y="86.36" rot="MR180"/>
<instance part="S6" gate="G$1" x="40.64" y="58.42" rot="MR180"/>
<instance part="SUPPLY20" gate="G$1" x="50.8" y="60.96" rot="MR0"/>
<instance part="GND18" gate="1" x="55.88" y="63.5" rot="MR180"/>
<instance part="S7" gate="G$1" x="160.02" y="162.56" rot="MR180"/>
<instance part="SUPPLY21" gate="G$1" x="170.18" y="165.1" rot="MR0"/>
<instance part="GND19" gate="1" x="175.26" y="167.64" rot="MR180"/>
<instance part="S8" gate="G$1" x="160.02" y="142.24" rot="MR180"/>
<instance part="SUPPLY22" gate="G$1" x="170.18" y="144.78" rot="MR0"/>
<instance part="GND20" gate="1" x="175.26" y="147.32" rot="MR180"/>
<instance part="S9" gate="G$1" x="160.02" y="121.92" rot="MR180"/>
<instance part="SUPPLY23" gate="G$1" x="170.18" y="124.46" rot="MR0"/>
<instance part="GND21" gate="1" x="175.26" y="127" rot="MR180"/>
<instance part="S0" gate="G$1" x="160.02" y="101.6" rot="MR180"/>
<instance part="SUPPLY24" gate="G$1" x="170.18" y="104.14" rot="MR0"/>
<instance part="GND22" gate="1" x="175.26" y="106.68" rot="MR180"/>
<instance part="SE" gate="G$1" x="160.02" y="81.28" rot="MR180"/>
<instance part="SUPPLY25" gate="G$1" x="170.18" y="83.82" rot="MR0"/>
<instance part="GND23" gate="1" x="175.26" y="86.36" rot="MR180"/>
<instance part="ST" gate="G$1" x="160.02" y="58.42" rot="MR180"/>
<instance part="SUPPLY26" gate="G$1" x="170.18" y="60.96" rot="MR0"/>
<instance part="GND24" gate="1" x="175.26" y="63.5" rot="MR180"/>
<instance part="IC1" gate="G$1" x="83.82" y="152.4"/>
<instance part="IC2" gate="G$1" x="83.82" y="111.76"/>
<instance part="IC3" gate="G$1" x="83.82" y="71.12"/>
<instance part="GND25" gate="1" x="73.66" y="142.24" rot="MR0"/>
<instance part="GND26" gate="1" x="93.98" y="142.24" rot="MR0"/>
<instance part="GND27" gate="1" x="93.98" y="101.6" rot="MR0"/>
<instance part="GND28" gate="1" x="73.66" y="101.6" rot="MR0"/>
<instance part="GND29" gate="1" x="73.66" y="60.96" rot="MR0"/>
<instance part="GND30" gate="1" x="93.98" y="60.96" rot="MR0"/>
<instance part="SUPPLY27" gate="G$1" x="73.66" y="157.48" rot="MR0"/>
<instance part="SUPPLY28" gate="G$1" x="93.98" y="157.48" rot="MR0"/>
<instance part="SUPPLY29" gate="G$1" x="73.66" y="116.84" rot="MR0"/>
<instance part="SUPPLY30" gate="G$1" x="93.98" y="116.84" rot="MR0"/>
<instance part="SUPPLY31" gate="G$1" x="73.66" y="76.2" rot="MR0"/>
<instance part="SUPPLY32" gate="G$1" x="93.98" y="76.2" rot="MR0"/>
<instance part="IC4" gate="G$1" x="200.66" y="152.4"/>
<instance part="IC5" gate="G$1" x="200.66" y="111.76"/>
<instance part="IC6" gate="G$1" x="200.66" y="71.12"/>
<instance part="GND31" gate="1" x="190.5" y="101.6" rot="MR0"/>
<instance part="GND32" gate="1" x="210.82" y="101.6" rot="MR0"/>
<instance part="GND33" gate="1" x="190.5" y="60.96" rot="MR0"/>
<instance part="GND34" gate="1" x="210.82" y="60.96" rot="MR0"/>
<instance part="GND35" gate="1" x="210.82" y="142.24" rot="MR0"/>
<instance part="GND36" gate="1" x="190.5" y="142.24" rot="MR0"/>
<instance part="SUPPLY33" gate="G$1" x="190.5" y="157.48" rot="MR0"/>
<instance part="SUPPLY34" gate="G$1" x="210.82" y="157.48" rot="MR0"/>
<instance part="SUPPLY35" gate="G$1" x="210.82" y="116.84" rot="MR0"/>
<instance part="SUPPLY36" gate="G$1" x="190.5" y="116.84" rot="MR0"/>
<instance part="SUPPLY37" gate="G$1" x="190.5" y="76.2" rot="MR0"/>
<instance part="SUPPLY38" gate="G$1" x="210.82" y="76.2" rot="MR0"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="228.6" y1="83.82" x2="228.6" y2="81.28" width="0.1524" layer="91"/>
<pinref part="BE" gate="G$1" pin="2"/>
<wire x1="228.6" y1="81.28" x2="236.22" y2="81.28" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND7" gate="1" pin="GND"/>
<wire x1="228.6" y1="60.96" x2="228.6" y2="58.42" width="0.1524" layer="91"/>
<pinref part="BT" gate="G$1" pin="2"/>
<wire x1="228.6" y1="58.42" x2="236.22" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="228.6" y1="104.14" x2="228.6" y2="101.6" width="0.1524" layer="91"/>
<pinref part="B0" gate="G$1" pin="2"/>
<wire x1="228.6" y1="101.6" x2="236.22" y2="101.6" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="228.6" y1="144.78" x2="228.6" y2="142.24" width="0.1524" layer="91"/>
<pinref part="B8" gate="G$1" pin="2"/>
<wire x1="228.6" y1="142.24" x2="236.22" y2="142.24" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="228.6" y1="165.1" x2="228.6" y2="162.56" width="0.1524" layer="91"/>
<pinref part="B7" gate="G$1" pin="2"/>
<wire x1="228.6" y1="162.56" x2="236.22" y2="162.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="228.6" y1="124.46" x2="228.6" y2="121.92" width="0.1524" layer="91"/>
<pinref part="B9" gate="G$1" pin="2"/>
<wire x1="228.6" y1="121.92" x2="236.22" y2="121.92" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND13" gate="1" pin="GND"/>
<wire x1="109.22" y1="165.1" x2="109.22" y2="162.56" width="0.1524" layer="91"/>
<pinref part="B1" gate="G$1" pin="2"/>
<wire x1="109.22" y1="162.56" x2="116.84" y2="162.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="109.22" y1="124.46" x2="109.22" y2="121.92" width="0.1524" layer="91"/>
<pinref part="B3" gate="G$1" pin="2"/>
<wire x1="109.22" y1="121.92" x2="116.84" y2="121.92" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND8" gate="1" pin="GND"/>
<wire x1="109.22" y1="144.78" x2="109.22" y2="142.24" width="0.1524" layer="91"/>
<pinref part="B2" gate="G$1" pin="2"/>
<wire x1="109.22" y1="142.24" x2="116.84" y2="142.24" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND10" gate="1" pin="GND"/>
<wire x1="109.22" y1="104.14" x2="109.22" y2="101.6" width="0.1524" layer="91"/>
<pinref part="B4" gate="G$1" pin="2"/>
<wire x1="109.22" y1="101.6" x2="116.84" y2="101.6" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND11" gate="1" pin="GND"/>
<wire x1="109.22" y1="60.96" x2="109.22" y2="58.42" width="0.1524" layer="91"/>
<pinref part="B6" gate="G$1" pin="2"/>
<wire x1="109.22" y1="58.42" x2="116.84" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND12" gate="1" pin="GND"/>
<wire x1="109.22" y1="83.82" x2="109.22" y2="81.28" width="0.1524" layer="91"/>
<pinref part="B5" gate="G$1" pin="2"/>
<wire x1="109.22" y1="81.28" x2="116.84" y2="81.28" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="55.88" y1="165.1" x2="55.88" y2="162.56" width="0.1524" layer="91"/>
<pinref part="S1" gate="G$1" pin="2"/>
<wire x1="55.88" y1="162.56" x2="48.26" y2="162.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND14" gate="1" pin="GND"/>
<wire x1="55.88" y1="144.78" x2="55.88" y2="142.24" width="0.1524" layer="91"/>
<pinref part="S2" gate="G$1" pin="2"/>
<wire x1="55.88" y1="142.24" x2="48.26" y2="142.24" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND15" gate="1" pin="GND"/>
<wire x1="55.88" y1="124.46" x2="55.88" y2="121.92" width="0.1524" layer="91"/>
<pinref part="S3" gate="G$1" pin="2"/>
<wire x1="55.88" y1="121.92" x2="48.26" y2="121.92" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND16" gate="1" pin="GND"/>
<wire x1="55.88" y1="104.14" x2="55.88" y2="101.6" width="0.1524" layer="91"/>
<pinref part="S4" gate="G$1" pin="2"/>
<wire x1="55.88" y1="101.6" x2="48.26" y2="101.6" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND17" gate="1" pin="GND"/>
<wire x1="55.88" y1="83.82" x2="55.88" y2="81.28" width="0.1524" layer="91"/>
<pinref part="S5" gate="G$1" pin="2"/>
<wire x1="55.88" y1="81.28" x2="48.26" y2="81.28" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND18" gate="1" pin="GND"/>
<wire x1="55.88" y1="60.96" x2="55.88" y2="58.42" width="0.1524" layer="91"/>
<pinref part="S6" gate="G$1" pin="2"/>
<wire x1="55.88" y1="58.42" x2="48.26" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND19" gate="1" pin="GND"/>
<wire x1="175.26" y1="165.1" x2="175.26" y2="162.56" width="0.1524" layer="91"/>
<pinref part="S7" gate="G$1" pin="2"/>
<wire x1="175.26" y1="162.56" x2="167.64" y2="162.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND20" gate="1" pin="GND"/>
<wire x1="175.26" y1="144.78" x2="175.26" y2="142.24" width="0.1524" layer="91"/>
<pinref part="S8" gate="G$1" pin="2"/>
<wire x1="175.26" y1="142.24" x2="167.64" y2="142.24" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND21" gate="1" pin="GND"/>
<wire x1="175.26" y1="124.46" x2="175.26" y2="121.92" width="0.1524" layer="91"/>
<pinref part="S9" gate="G$1" pin="2"/>
<wire x1="175.26" y1="121.92" x2="167.64" y2="121.92" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND22" gate="1" pin="GND"/>
<wire x1="175.26" y1="104.14" x2="175.26" y2="101.6" width="0.1524" layer="91"/>
<pinref part="S0" gate="G$1" pin="2"/>
<wire x1="175.26" y1="101.6" x2="167.64" y2="101.6" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND23" gate="1" pin="GND"/>
<wire x1="175.26" y1="83.82" x2="175.26" y2="81.28" width="0.1524" layer="91"/>
<pinref part="SE" gate="G$1" pin="2"/>
<wire x1="175.26" y1="81.28" x2="167.64" y2="81.28" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND24" gate="1" pin="GND"/>
<wire x1="175.26" y1="60.96" x2="175.26" y2="58.42" width="0.1524" layer="91"/>
<pinref part="ST" gate="G$1" pin="2"/>
<wire x1="175.26" y1="58.42" x2="167.64" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND33" gate="1" pin="GND"/>
<pinref part="IC6" gate="G$1" pin="GND"/>
<wire x1="190.5" y1="63.5" x2="190.5" y2="66.04" width="0.1524" layer="91"/>
<wire x1="190.5" y1="66.04" x2="193.04" y2="66.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND34" gate="1" pin="GND"/>
<pinref part="IC6" gate="G$1" pin="GND@2"/>
<wire x1="210.82" y1="63.5" x2="210.82" y2="66.04" width="0.1524" layer="91"/>
<wire x1="210.82" y1="66.04" x2="208.28" y2="66.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND32" gate="1" pin="GND"/>
<pinref part="IC5" gate="G$1" pin="GND@2"/>
<wire x1="210.82" y1="104.14" x2="210.82" y2="106.68" width="0.1524" layer="91"/>
<wire x1="210.82" y1="106.68" x2="208.28" y2="106.68" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND31" gate="1" pin="GND"/>
<pinref part="IC5" gate="G$1" pin="GND"/>
<wire x1="190.5" y1="104.14" x2="190.5" y2="106.68" width="0.1524" layer="91"/>
<wire x1="190.5" y1="106.68" x2="193.04" y2="106.68" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND36" gate="1" pin="GND"/>
<pinref part="IC4" gate="G$1" pin="GND"/>
<wire x1="190.5" y1="144.78" x2="190.5" y2="147.32" width="0.1524" layer="91"/>
<wire x1="190.5" y1="147.32" x2="193.04" y2="147.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND35" gate="1" pin="GND"/>
<pinref part="IC4" gate="G$1" pin="GND@2"/>
<wire x1="210.82" y1="144.78" x2="210.82" y2="147.32" width="0.1524" layer="91"/>
<wire x1="210.82" y1="147.32" x2="208.28" y2="147.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND25" gate="1" pin="GND"/>
<pinref part="IC1" gate="G$1" pin="GND"/>
<wire x1="73.66" y1="144.78" x2="73.66" y2="147.32" width="0.1524" layer="91"/>
<wire x1="73.66" y1="147.32" x2="76.2" y2="147.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND26" gate="1" pin="GND"/>
<pinref part="IC1" gate="G$1" pin="GND@2"/>
<wire x1="93.98" y1="144.78" x2="93.98" y2="147.32" width="0.1524" layer="91"/>
<wire x1="93.98" y1="147.32" x2="91.44" y2="147.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND27" gate="1" pin="GND"/>
<pinref part="IC2" gate="G$1" pin="GND@2"/>
<wire x1="93.98" y1="104.14" x2="93.98" y2="106.68" width="0.1524" layer="91"/>
<wire x1="93.98" y1="106.68" x2="91.44" y2="106.68" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND28" gate="1" pin="GND"/>
<pinref part="IC2" gate="G$1" pin="GND"/>
<wire x1="73.66" y1="104.14" x2="73.66" y2="106.68" width="0.1524" layer="91"/>
<wire x1="73.66" y1="106.68" x2="76.2" y2="106.68" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND30" gate="1" pin="GND"/>
<pinref part="IC3" gate="G$1" pin="GND@2"/>
<wire x1="93.98" y1="63.5" x2="93.98" y2="66.04" width="0.1524" layer="91"/>
<wire x1="93.98" y1="66.04" x2="91.44" y2="66.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND29" gate="1" pin="GND"/>
<pinref part="IC3" gate="G$1" pin="GND"/>
<wire x1="73.66" y1="63.5" x2="73.66" y2="66.04" width="0.1524" layer="91"/>
<wire x1="73.66" y1="66.04" x2="76.2" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="SUPPLY3" gate="G$1" pin="VCC"/>
<pinref part="B7" gate="G$1" pin="1"/>
<wire x1="233.68" y1="165.1" x2="236.22" y2="165.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY1" gate="G$1" pin="VCC"/>
<pinref part="B8" gate="G$1" pin="1"/>
<wire x1="233.68" y1="144.78" x2="236.22" y2="144.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY4" gate="G$1" pin="VCC"/>
<pinref part="B0" gate="G$1" pin="1"/>
<wire x1="233.68" y1="104.14" x2="236.22" y2="104.14" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY5" gate="G$1" pin="VCC"/>
<pinref part="B9" gate="G$1" pin="1"/>
<wire x1="233.68" y1="124.46" x2="236.22" y2="124.46" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY6" gate="G$1" pin="VCC"/>
<pinref part="BE" gate="G$1" pin="1"/>
<wire x1="233.68" y1="83.82" x2="236.22" y2="83.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY7" gate="G$1" pin="VCC"/>
<pinref part="BT" gate="G$1" pin="1"/>
<wire x1="233.68" y1="60.96" x2="236.22" y2="60.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY8" gate="G$1" pin="VCC"/>
<pinref part="B1" gate="G$1" pin="1"/>
<wire x1="114.3" y1="165.1" x2="116.84" y2="165.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY9" gate="G$1" pin="VCC"/>
<pinref part="B2" gate="G$1" pin="1"/>
<wire x1="114.3" y1="144.78" x2="116.84" y2="144.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY11" gate="G$1" pin="VCC"/>
<pinref part="B4" gate="G$1" pin="1"/>
<wire x1="114.3" y1="104.14" x2="116.84" y2="104.14" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY13" gate="G$1" pin="VCC"/>
<pinref part="B6" gate="G$1" pin="1"/>
<wire x1="114.3" y1="60.96" x2="116.84" y2="60.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY12" gate="G$1" pin="VCC"/>
<pinref part="B5" gate="G$1" pin="1"/>
<wire x1="114.3" y1="83.82" x2="116.84" y2="83.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY10" gate="G$1" pin="VCC"/>
<pinref part="B3" gate="G$1" pin="1"/>
<wire x1="114.3" y1="124.46" x2="116.84" y2="124.46" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY2" gate="G$1" pin="VCC"/>
<pinref part="S1" gate="G$1" pin="1"/>
<wire x1="50.8" y1="165.1" x2="48.26" y2="165.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY16" gate="G$1" pin="VCC"/>
<pinref part="S2" gate="G$1" pin="1"/>
<wire x1="50.8" y1="144.78" x2="48.26" y2="144.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY17" gate="G$1" pin="VCC"/>
<pinref part="S3" gate="G$1" pin="1"/>
<wire x1="50.8" y1="124.46" x2="48.26" y2="124.46" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY18" gate="G$1" pin="VCC"/>
<pinref part="S4" gate="G$1" pin="1"/>
<wire x1="50.8" y1="104.14" x2="48.26" y2="104.14" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY19" gate="G$1" pin="VCC"/>
<pinref part="S5" gate="G$1" pin="1"/>
<wire x1="50.8" y1="83.82" x2="48.26" y2="83.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY20" gate="G$1" pin="VCC"/>
<pinref part="S6" gate="G$1" pin="1"/>
<wire x1="50.8" y1="60.96" x2="48.26" y2="60.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY21" gate="G$1" pin="VCC"/>
<pinref part="S7" gate="G$1" pin="1"/>
<wire x1="170.18" y1="165.1" x2="167.64" y2="165.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY22" gate="G$1" pin="VCC"/>
<pinref part="S8" gate="G$1" pin="1"/>
<wire x1="170.18" y1="144.78" x2="167.64" y2="144.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY23" gate="G$1" pin="VCC"/>
<pinref part="S9" gate="G$1" pin="1"/>
<wire x1="170.18" y1="124.46" x2="167.64" y2="124.46" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY24" gate="G$1" pin="VCC"/>
<pinref part="S0" gate="G$1" pin="1"/>
<wire x1="170.18" y1="104.14" x2="167.64" y2="104.14" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY25" gate="G$1" pin="VCC"/>
<pinref part="SE" gate="G$1" pin="1"/>
<wire x1="170.18" y1="83.82" x2="167.64" y2="83.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY26" gate="G$1" pin="VCC"/>
<pinref part="ST" gate="G$1" pin="1"/>
<wire x1="170.18" y1="60.96" x2="167.64" y2="60.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY37" gate="G$1" pin="VCC"/>
<pinref part="IC6" gate="G$1" pin="VCC"/>
<wire x1="190.5" y1="76.2" x2="190.5" y2="73.66" width="0.1524" layer="91"/>
<wire x1="190.5" y1="73.66" x2="193.04" y2="73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY38" gate="G$1" pin="VCC"/>
<pinref part="IC6" gate="G$1" pin="VCC@2"/>
<wire x1="210.82" y1="76.2" x2="210.82" y2="73.66" width="0.1524" layer="91"/>
<wire x1="210.82" y1="73.66" x2="208.28" y2="73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY35" gate="G$1" pin="VCC"/>
<pinref part="IC5" gate="G$1" pin="VCC@2"/>
<wire x1="210.82" y1="116.84" x2="210.82" y2="114.3" width="0.1524" layer="91"/>
<wire x1="210.82" y1="114.3" x2="208.28" y2="114.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY36" gate="G$1" pin="VCC"/>
<pinref part="IC5" gate="G$1" pin="VCC"/>
<wire x1="190.5" y1="116.84" x2="190.5" y2="114.3" width="0.1524" layer="91"/>
<wire x1="190.5" y1="114.3" x2="193.04" y2="114.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY33" gate="G$1" pin="VCC"/>
<pinref part="IC4" gate="G$1" pin="VCC"/>
<wire x1="190.5" y1="157.48" x2="190.5" y2="154.94" width="0.1524" layer="91"/>
<wire x1="190.5" y1="154.94" x2="193.04" y2="154.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY34" gate="G$1" pin="VCC"/>
<pinref part="IC4" gate="G$1" pin="VCC@2"/>
<wire x1="210.82" y1="157.48" x2="210.82" y2="154.94" width="0.1524" layer="91"/>
<wire x1="210.82" y1="154.94" x2="208.28" y2="154.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY27" gate="G$1" pin="VCC"/>
<pinref part="IC1" gate="G$1" pin="VCC"/>
<wire x1="73.66" y1="157.48" x2="73.66" y2="154.94" width="0.1524" layer="91"/>
<wire x1="73.66" y1="154.94" x2="76.2" y2="154.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY28" gate="G$1" pin="VCC"/>
<pinref part="IC1" gate="G$1" pin="VCC@2"/>
<wire x1="93.98" y1="157.48" x2="93.98" y2="154.94" width="0.1524" layer="91"/>
<wire x1="93.98" y1="154.94" x2="91.44" y2="154.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY29" gate="G$1" pin="VCC"/>
<wire x1="73.66" y1="116.84" x2="73.66" y2="114.3" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="VCC"/>
<wire x1="73.66" y1="114.3" x2="76.2" y2="114.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY30" gate="G$1" pin="VCC"/>
<pinref part="IC2" gate="G$1" pin="VCC@2"/>
<wire x1="93.98" y1="116.84" x2="93.98" y2="114.3" width="0.1524" layer="91"/>
<wire x1="93.98" y1="114.3" x2="91.44" y2="114.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY31" gate="G$1" pin="VCC"/>
<pinref part="IC3" gate="G$1" pin="VCC"/>
<wire x1="73.66" y1="76.2" x2="73.66" y2="73.66" width="0.1524" layer="91"/>
<wire x1="73.66" y1="73.66" x2="76.2" y2="73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY32" gate="G$1" pin="VCC"/>
<pinref part="IC3" gate="G$1" pin="VCC@2"/>
<wire x1="93.98" y1="76.2" x2="93.98" y2="73.66" width="0.1524" layer="91"/>
<wire x1="93.98" y1="73.66" x2="91.44" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="S1" gate="G$1" pin="3"/>
<wire x1="48.26" y1="160.02" x2="66.04" y2="160.02" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="IO2"/>
<wire x1="66.04" y1="160.02" x2="66.04" y2="149.86" width="0.1524" layer="91"/>
<wire x1="66.04" y1="149.86" x2="76.2" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="S2" gate="G$1" pin="3"/>
<wire x1="48.26" y1="139.7" x2="63.5" y2="139.7" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="IO1"/>
<wire x1="63.5" y1="139.7" x2="63.5" y2="152.4" width="0.1524" layer="91"/>
<wire x1="63.5" y1="152.4" x2="76.2" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="B1" gate="G$1" pin="3"/>
<wire x1="116.84" y1="160.02" x2="101.6" y2="160.02" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="IO2@2"/>
<wire x1="101.6" y1="160.02" x2="101.6" y2="149.86" width="0.1524" layer="91"/>
<wire x1="101.6" y1="149.86" x2="91.44" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="B2" gate="G$1" pin="3"/>
<wire x1="116.84" y1="139.7" x2="104.14" y2="139.7" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="IO1@2"/>
<wire x1="104.14" y1="139.7" x2="104.14" y2="152.4" width="0.1524" layer="91"/>
<wire x1="104.14" y1="152.4" x2="91.44" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="S3" gate="G$1" pin="3"/>
<wire x1="48.26" y1="119.38" x2="66.04" y2="119.38" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="IO2"/>
<wire x1="66.04" y1="119.38" x2="66.04" y2="109.22" width="0.1524" layer="91"/>
<wire x1="66.04" y1="109.22" x2="76.2" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="B3" gate="G$1" pin="3"/>
<wire x1="116.84" y1="119.38" x2="101.6" y2="119.38" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="IO2@2"/>
<wire x1="101.6" y1="119.38" x2="101.6" y2="109.22" width="0.1524" layer="91"/>
<wire x1="101.6" y1="109.22" x2="91.44" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="S4" gate="G$1" pin="3"/>
<wire x1="48.26" y1="99.06" x2="63.5" y2="99.06" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="IO1"/>
<wire x1="63.5" y1="99.06" x2="63.5" y2="111.76" width="0.1524" layer="91"/>
<wire x1="63.5" y1="111.76" x2="76.2" y2="111.76" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="B4" gate="G$1" pin="3"/>
<wire x1="116.84" y1="99.06" x2="104.14" y2="99.06" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="IO1@2"/>
<wire x1="104.14" y1="99.06" x2="104.14" y2="111.76" width="0.1524" layer="91"/>
<wire x1="104.14" y1="111.76" x2="91.44" y2="111.76" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="S5" gate="G$1" pin="3"/>
<wire x1="48.26" y1="78.74" x2="66.04" y2="78.74" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$1" pin="IO2"/>
<wire x1="66.04" y1="78.74" x2="66.04" y2="68.58" width="0.1524" layer="91"/>
<wire x1="66.04" y1="68.58" x2="76.2" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="B5" gate="G$1" pin="3"/>
<wire x1="116.84" y1="78.74" x2="101.6" y2="78.74" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$1" pin="IO2@2"/>
<wire x1="101.6" y1="78.74" x2="101.6" y2="68.58" width="0.1524" layer="91"/>
<wire x1="101.6" y1="68.58" x2="91.44" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="S6" gate="G$1" pin="3"/>
<wire x1="48.26" y1="55.88" x2="63.5" y2="55.88" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$1" pin="IO1"/>
<wire x1="63.5" y1="55.88" x2="63.5" y2="71.12" width="0.1524" layer="91"/>
<wire x1="63.5" y1="71.12" x2="76.2" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="B6" gate="G$1" pin="3"/>
<wire x1="116.84" y1="55.88" x2="104.14" y2="55.88" width="0.1524" layer="91"/>
<wire x1="104.14" y1="55.88" x2="104.14" y2="71.12" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$1" pin="IO1@2"/>
<wire x1="104.14" y1="71.12" x2="91.44" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="S7" gate="G$1" pin="3"/>
<wire x1="167.64" y1="160.02" x2="182.88" y2="160.02" width="0.1524" layer="91"/>
<pinref part="IC4" gate="G$1" pin="IO2"/>
<wire x1="182.88" y1="160.02" x2="182.88" y2="149.86" width="0.1524" layer="91"/>
<wire x1="182.88" y1="149.86" x2="193.04" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="S8" gate="G$1" pin="3"/>
<wire x1="167.64" y1="139.7" x2="180.34" y2="139.7" width="0.1524" layer="91"/>
<wire x1="180.34" y1="139.7" x2="180.34" y2="152.4" width="0.1524" layer="91"/>
<wire x1="180.34" y1="152.4" x2="193.04" y2="152.4" width="0.1524" layer="91"/>
<pinref part="IC4" gate="G$1" pin="IO1"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="B8" gate="G$1" pin="3"/>
<wire x1="236.22" y1="139.7" x2="223.52" y2="139.7" width="0.1524" layer="91"/>
<pinref part="IC4" gate="G$1" pin="IO1@2"/>
<wire x1="223.52" y1="139.7" x2="223.52" y2="152.4" width="0.1524" layer="91"/>
<wire x1="223.52" y1="152.4" x2="208.28" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="B7" gate="G$1" pin="3"/>
<wire x1="236.22" y1="160.02" x2="220.98" y2="160.02" width="0.1524" layer="91"/>
<pinref part="IC4" gate="G$1" pin="IO2@2"/>
<wire x1="220.98" y1="160.02" x2="220.98" y2="149.86" width="0.1524" layer="91"/>
<wire x1="220.98" y1="149.86" x2="208.28" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="S9" gate="G$1" pin="3"/>
<wire x1="167.64" y1="119.38" x2="182.88" y2="119.38" width="0.1524" layer="91"/>
<pinref part="IC5" gate="G$1" pin="IO2"/>
<wire x1="182.88" y1="119.38" x2="182.88" y2="109.22" width="0.1524" layer="91"/>
<wire x1="182.88" y1="109.22" x2="193.04" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="B9" gate="G$1" pin="3"/>
<wire x1="236.22" y1="119.38" x2="220.98" y2="119.38" width="0.1524" layer="91"/>
<pinref part="IC5" gate="G$1" pin="IO2@2"/>
<wire x1="220.98" y1="119.38" x2="220.98" y2="109.22" width="0.1524" layer="91"/>
<wire x1="220.98" y1="109.22" x2="208.28" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="SE" gate="G$1" pin="3"/>
<wire x1="167.64" y1="78.74" x2="182.88" y2="78.74" width="0.1524" layer="91"/>
<pinref part="IC6" gate="G$1" pin="IO2"/>
<wire x1="182.88" y1="78.74" x2="182.88" y2="68.58" width="0.1524" layer="91"/>
<wire x1="182.88" y1="68.58" x2="193.04" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="BE" gate="G$1" pin="3"/>
<wire x1="236.22" y1="78.74" x2="236.22" y2="76.2" width="0.1524" layer="91"/>
<wire x1="236.22" y1="76.2" x2="220.98" y2="76.2" width="0.1524" layer="91"/>
<pinref part="IC6" gate="G$1" pin="IO2@2"/>
<wire x1="220.98" y1="76.2" x2="220.98" y2="68.58" width="0.1524" layer="91"/>
<wire x1="220.98" y1="68.58" x2="208.28" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="ST" gate="G$1" pin="3"/>
<wire x1="167.64" y1="55.88" x2="180.34" y2="55.88" width="0.1524" layer="91"/>
<pinref part="IC6" gate="G$1" pin="IO1"/>
<wire x1="180.34" y1="55.88" x2="180.34" y2="71.12" width="0.1524" layer="91"/>
<wire x1="180.34" y1="71.12" x2="193.04" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="BT" gate="G$1" pin="3"/>
<wire x1="236.22" y1="55.88" x2="218.44" y2="55.88" width="0.1524" layer="91"/>
<pinref part="IC6" gate="G$1" pin="IO1@2"/>
<wire x1="218.44" y1="55.88" x2="218.44" y2="71.12" width="0.1524" layer="91"/>
<wire x1="218.44" y1="71.12" x2="208.28" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="S0" gate="G$1" pin="3"/>
<wire x1="167.64" y1="99.06" x2="180.34" y2="99.06" width="0.1524" layer="91"/>
<pinref part="IC5" gate="G$1" pin="IO1"/>
<wire x1="180.34" y1="99.06" x2="180.34" y2="111.76" width="0.1524" layer="91"/>
<wire x1="180.34" y1="111.76" x2="193.04" y2="111.76" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="B0" gate="G$1" pin="3"/>
<wire x1="236.22" y1="99.06" x2="218.44" y2="99.06" width="0.1524" layer="91"/>
<pinref part="IC5" gate="G$1" pin="IO1@2"/>
<wire x1="218.44" y1="99.06" x2="218.44" y2="111.76" width="0.1524" layer="91"/>
<wire x1="218.44" y1="111.76" x2="208.28" y2="111.76" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="113,1,239.437,161.095,B7,,,,,"/>
<approved hash="113,1,239.437,120.455,B9,,,,,"/>
<approved hash="113,1,239.437,79.8153,BE,,,,,"/>
<approved hash="113,1,120.057,161.095,B1,,,,,"/>
<approved hash="113,1,120.057,120.455,B3,,,,,"/>
<approved hash="113,1,120.057,79.8153,B5,,,,,"/>
<approved hash="113,1,239.437,140.775,B8,,,,,"/>
<approved hash="113,1,239.437,100.135,B0,,,,,"/>
<approved hash="113,1,239.437,56.9553,BT,,,,,"/>
<approved hash="113,1,120.057,140.775,B2,,,,,"/>
<approved hash="113,1,120.057,100.135,B4,,,,,"/>
<approved hash="113,1,120.057,56.9553,B6,,,,,"/>
<approved hash="113,1,45.0427,161.095,S1,,,,,"/>
<approved hash="113,1,45.0427,140.775,S2,,,,,"/>
<approved hash="113,1,45.0427,120.455,S3,,,,,"/>
<approved hash="113,1,45.0427,100.135,S4,,,,,"/>
<approved hash="113,1,45.0427,79.8153,S5,,,,,"/>
<approved hash="113,1,45.0427,56.9553,S6,,,,,"/>
<approved hash="113,1,164.423,161.095,S7,,,,,"/>
<approved hash="113,1,164.423,140.775,S8,,,,,"/>
<approved hash="113,1,164.423,120.455,S9,,,,,"/>
<approved hash="113,1,164.423,100.135,S0,,,,,"/>
<approved hash="113,1,164.423,79.8153,SE,,,,,"/>
<approved hash="113,1,164.423,56.9553,ST,,,,,"/>
</errors>
</schematic>
</drawing>
</eagle>
