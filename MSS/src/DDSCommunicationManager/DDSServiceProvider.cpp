#include "DDSServiceProvider.h"     

/************************************************************************
	Constructor / Destructor
************************************************************************/
DDSServiceProvider::DDSServiceProvider()
{
	initializeDDS();
}

DDSServiceProvider::~DDSServiceProvider()
{
	releaseDDS();
}

void
DDSServiceProvider::initializeDDS()
{
	participant = nullptr;
	publisher = nullptr;
}

void
DDSServiceProvider::releaseDDS()
{
	participant = nullptr;
	publisher = nullptr;
}

/************************************************************************
	DDS Services
************************************************************************/
DDSDomainParticipant*
DDSServiceProvider::createDomainParticipant(int domainID/*, std::string project*/)
{
	// [23.10.26] QoS Default 값으로 수정 - hs
	/*
	char* projectParticipant = "";
	constexpr char* DDS_QOS_LIBRARY_NAME = "DDSSim_Library";
	constexpr char* DDS_QOS_PARTICIPANT_LITS = "LSAM_LITS_ParticipantProfile";
	constexpr char* DDS_QOS_PARTICIPANT_TB = "LSAM_TB_ParticipantProfile";

	if (project == "LITS")
		projectParticipant = DDS_QOS_PARTICIPANT_LITS;
	else
		projectParticipant = DDS_QOS_PARTICIPANT_TB;

	participant = DDSTheParticipantFactory->create_participant_with_profile(domainID, DDS_QOS_LIBRARY_NAME, projectParticipant, nullptr listener, DDS_STATUS_MASK_NONE); */
	participant = DDSTheParticipantFactory->create_participant(domainID, DDS_PARTICIPANT_QOS_DEFAULT, nullptr/*listener*/, DDS_STATUS_MASK_NONE);
	
	return participant;
}

int
DDSServiceProvider::deleteDomainParticipant(DDSDomainParticipant* participant)
{
	DDS_ReturnCode_t retCode;
	int status = 0;

	retCode = participant->delete_contained_entities();
	if (retCode != DDS_RETCODE_OK)
	{
		std::cerr << "delete_contained_entities error: " << retCode;
		status = -1;
	}

	retCode = DDSTheParticipantFactory->delete_participant(participant);
	if (retCode != DDS_RETCODE_OK)
	{
		std::cerr << "delete_participant error: " << retCode;
		status = -1;
	}

	return status;
}

DDSPublisher*
DDSServiceProvider::createPublisher()
{
	publisher = participant->create_publisher(DDS_PUBLISHER_QOS_DEFAULT, nullptr/* listener */, DDS_STATUS_MASK_NONE);
	return publisher;
}

void
DDSServiceProvider::deletePublisher(DDSPublisher* publisher)
{
	participant->delete_publisher(publisher);
}

DDSSubscriber*
DDSServiceProvider::createSubscriber()
{
	subscriber = participant->create_subscriber(DDS_SUBSCRIBER_QOS_DEFAULT, nullptr/* listener */, DDS_STATUS_MASK_NONE);
	return subscriber;
}

void
DDSServiceProvider::deleteSubscriber(DDSSubscriber* subscriber)
{
	participant->delete_subscriber(subscriber);
}

DDSTopic*
DDSServiceProvider::createTopic(std::string topicName, std::string typeName)
{
	participant->get_default_topic_qos(topicQos);
	topicQos.reliability.kind = DDS_BEST_EFFORT_RELIABILITY_QOS;
	topicQos.durability.kind = DDS_VOLATILE_DURABILITY_QOS;

	participant->set_default_topic_qos(topicQos);
	topic = participant->create_topic(topicName.c_str(), typeName.c_str(), DDS_TOPIC_QOS_DEFAULT, nullptr /* listener */, DDS_STATUS_MASK_NONE);

	return topic;
}

void
DDSServiceProvider::deleteTopic(DDSTopic* topicInstance)
{
	participant->delete_topic(topicInstance);
}

DDSDataWriter*
DDSServiceProvider::createWriter()
{	
	writer = publisher->create_datawriter(topic, DDS_DATAWRITER_QOS_DEFAULT, nullptr /* listener */, DDS_STATUS_MASK_NONE);
	return writer;
}

void
DDSServiceProvider::deleteWriter(DDSDataWriter* writer)
{
	participant->delete_datawriter(writer);
}

void
DDSServiceProvider::registerReaderListener(DDSDataReaderListener* readerListener)
{
	this->readerListener = readerListener;
}

DDSDataReader*
DDSServiceProvider::createReader()
{
	reader = subscriber->create_datareader(topic, DDS_DATAREADER_QOS_DEFAULT, readerListener, DDS_STATUS_MASK_ALL);
	return reader;
}

void
DDSServiceProvider::deleteReader(DDSDataReader* reader)
{
	// if need be, write your code
}

DDSDomainParticipant*
DDSServiceProvider::getDomainParticipant()
{
	return participant;
}