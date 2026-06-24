#pragma once
#include <iostream>
#include "DDSSimGen/DDSSim.h"
#include "DDSSimGen/DDSSimSupport.h"

class DDSServiceProvider
{
public:
	DDSServiceProvider();
	~DDSServiceProvider();

public:
	DDSDomainParticipant* createDomainParticipant(int domainID/*, std::string project*/);
	int deleteDomainParticipant(DDSDomainParticipant* participant);
	DDSPublisher* createPublisher();
	void deletePublisher(DDSPublisher* publisher);
	DDSSubscriber* createSubscriber();
	void deleteSubscriber(DDSSubscriber* subscriber);
	DDSTopic* createTopic(std::string topicName, std::string typeName);
	void deleteTopic(DDSTopic* topicInstance);
	DDSDataWriter* createWriter();
	void deleteWriter(DDSDataWriter* writer);
	DDSDataReader* createReader();
	void deleteReader(DDSDataReader* reader);
	DDSDomainParticipant* getDomainParticipant();
	void registerReaderListener(DDSDataReaderListener* readerListener);

private:
	void initializeDDS();
	void releaseDDS();

private:
	int domainID;
	std::string typeName;
	DDSDomainParticipant* participant;
	DDSPublisher* publisher;
	DDSSubscriber* subscriber;
	DDSDataWriter* writer;
	DDSDataReader* reader;
	DDSTopic* topic;
	DDS_TopicQos topicQos;
	DDSDataReaderListener* readerListener;
};

