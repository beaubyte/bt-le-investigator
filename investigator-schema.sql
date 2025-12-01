-- DROP SCHEMA bluetooth;

CREATE SCHEMA bluetooth AUTHORIZATION [user];

-- DROP SEQUENCE bluetooth.device_events_eventid_seq;

CREATE SEQUENCE bluetooth.device_events_eventid_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 2147483647
	START 1
	CACHE 1
	NO CYCLE;
-- DROP SEQUENCE bluetooth.findable_deviceid_seq;

CREATE SEQUENCE bluetooth.findable_deviceid_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 32767
	START 1
	CACHE 1
	NO CYCLE;
-- DROP SEQUENCE bluetooth.people_personid_seq;

CREATE SEQUENCE bluetooth.people_personid_seq
	INCREMENT BY 1
	MINVALUE 1
	MAXVALUE 32767
	START 1
	CACHE 1
	NO CYCLE;-- bluetooth.device_events definition

-- Drop table

-- DROP TABLE bluetooth.device_events;

CREATE TABLE bluetooth.device_events (
	macaddress macaddr NOT NULL,
	"time" timestamp NULL,
	"location" varchar NULL,
	"name" varchar NULL,
	eventid serial4 NOT NULL,
	CONSTRAINT device_events_pk PRIMARY KEY (eventid)
);


-- bluetooth.people definition

-- Drop table

-- DROP TABLE bluetooth.people;

CREATE TABLE bluetooth.people (
	"name" varchar NULL,
	personid smallserial NOT NULL,
	CONSTRAINT people_pk PRIMARY KEY (personid)
);


-- bluetooth.findable definition

-- Drop table

-- DROP TABLE bluetooth.findable;

CREATE TABLE bluetooth.findable (
	macaddress macaddr NOT NULL,
	friendlyname varchar NULL,
	istile bool NULL,
	personid int4 NULL,
	deviceid smallserial NOT NULL,
	CONSTRAINT findable_pk PRIMARY KEY (deviceid),
	CONSTRAINT findable_people_fk FOREIGN KEY (personid) REFERENCES bluetooth.people(personid)
);
